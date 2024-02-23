/***************************************************************************************
* Copyright (c) 2014-2022 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include <cpu/cpu.h>
#include <cpu/decode.h>
#include <cpu/difftest.h>
#include <locale.h>
#include <cpu/ifetch.h>
#include <stdlib.h>

/* The assembly code of instructions executed is only output to the screen
 * when the number of instructions executed is less than this value.
 * This is useful when you use the `si' command.
 * You can modify this value as you want.
 */
#define MAX_INST_TO_PRINT 10
#define RINGBUFF_LEN 10

CPU_state cpu = {};
uint64_t g_nr_guest_inst = 0;
static uint64_t g_timer = 0;                  // unit: us
static bool g_print_step = false;

void device_update();
int Ringbuff_Write(Decode *s);
void Ringbuff_Print();
// void Dtrace_Print();

static void trace_and_difftest(Decode *_this, vaddr_t dnpc) {
#ifdef CONFIG_ITRACE_COND
  if (ITRACE_COND) { log_write("%s\n", _this->logbuf); }
#endif
  if (g_print_step) { IFDEF(CONFIG_ITRACE, puts(_this->logbuf)); }
  IFDEF(CONFIG_DIFFTEST, difftest_step(_this->pc, dnpc));
}

static void exec_once(Decode *s, vaddr_t pc) {
  s->pc = pc;
  s->snpc = pc;
  isa_exec_once(s);
  cpu.pc = s->dnpc;
  // printf("PC: 0x%lx\n", pc);
  // printf("MCAUSE: %lx\n", cpu.csr[mcause]);
#ifdef CONFIG_ITRACE
  char *p = s->logbuf;
  p += snprintf(p, sizeof(s->logbuf), FMT_WORD ":", s->pc);
  int ilen = s->snpc - s->pc;
  int i;
  uint8_t *inst = (uint8_t *)&s->isa.inst.val;
  for (i = ilen - 1; i >= 0; i --) {
    p += snprintf(p, 4, " %02x", inst[i]);
  }
  int ilen_max = MUXDEF(CONFIG_ISA_x86, 8, 4);
  int space_len = ilen_max - ilen;
  if (space_len < 0) space_len = 0;
  space_len = space_len * 3 + 1;
  memset(p, ' ', space_len);
  p += space_len;

  void disassemble(char *str, int size, uint64_t pc, uint8_t *code, int nbyte);
  disassemble(p, s->logbuf + sizeof(s->logbuf) - p,
      MUXDEF(CONFIG_ISA_x86, s->snpc, s->pc), (uint8_t *)&s->isa.inst.val, ilen);

  // printf("PC: 0x%lx\n", pc);
  // if(cpu.csr[mcause] != 0)
  //    printf("MCAUSE: %lx\n", cpu.csr[mcause]);
  // isa_reg_display();
#endif
#ifdef CONFIG_IRINGBUF
  Ringbuff_Write(s);
  Ringbuff_Print();
#endif
#ifdef CONFIG_FTRACE_COND
  void ftrace_judge(uint64_t pc, uint64_t dnpc, int is_call);
  if (s->dnpc != s->pc)
    ftrace_judge(s->pc, s->dnpc, ((BITS(s->isa.inst.val, 6, 0) == 0x6F || BITS(s->isa.inst.val, 6, 0) == 0x67) && BITS(s->isa.inst.val, 11, 7) == 0X1));
#endif
  // Dtrace_Print();
}

static void execute(uint64_t n) {
  Decode s;
  for (;n > 0; n --) {
    exec_once(&s, cpu.pc);
    g_nr_guest_inst ++;
    trace_and_difftest(&s, cpu.pc);
    if (nemu_state.state != NEMU_RUNNING) break;
    IFDEF(CONFIG_DEVICE, device_update());
  }
}

static void statistic() {
  IFNDEF(CONFIG_TARGET_AM, setlocale(LC_NUMERIC, ""));
#define NUMBERIC_FMT MUXDEF(CONFIG_TARGET_AM, "%", "%'") PRIu64
  Log("host time spent = " NUMBERIC_FMT " us", g_timer);
  Log("total guest instructions = " NUMBERIC_FMT, g_nr_guest_inst);
  if (g_timer > 0) Log("simulation frequency = " NUMBERIC_FMT " inst/s", g_nr_guest_inst * 1000000 / g_timer);
  else Log("Finish running in less than 1 us and can not calculate the simulation frequency");
}

void assert_fail_msg() {
  isa_reg_display();
  statistic();
}

/* Simulate how the CPU works. */
void cpu_exec(uint64_t n) {
  g_print_step = (n < MAX_INST_TO_PRINT);
  switch (nemu_state.state) {
    case NEMU_END: case NEMU_ABORT:
      printf("Program execution has ended. To restart the program, exit NEMU and run again.\n");
      exit(0);
      return;
    default: nemu_state.state = NEMU_RUNNING;
  }

  uint64_t timer_start = get_time();

  execute(n);

  uint64_t timer_end = get_time();
  g_timer += timer_end - timer_start;

  switch (nemu_state.state) {
    case NEMU_RUNNING: nemu_state.state = NEMU_STOP; break;

    case NEMU_END: case NEMU_ABORT:
      Log("nemu: %s at pc = " FMT_WORD,
          (nemu_state.state == NEMU_ABORT ? ANSI_FMT("ABORT", ANSI_FG_RED) :
           (nemu_state.halt_ret == 0 ? ANSI_FMT("HIT GOOD TRAP", ANSI_FG_GREEN) :
            ANSI_FMT("HIT BAD TRAP", ANSI_FG_RED))),
          nemu_state.halt_pc);
      // fall through
    case NEMU_QUIT: statistic();
  }
  #ifdef CONFIG_FTRACE_COND
    void print_ftrace();
    print_ftrace();
  #endif
}

// Iringbuff: As the program is wrong, print the latest ten instructions
#ifdef CONFIG_IRINGBUF
typedef struct {
  uint16_t Head;
  uint16_t Location;
  uint64_t Ringbuff[RINGBUFF_LEN];
} Ringbuff_t;

Ringbuff_t iringbuff;

void Ringbuff_Init() {
  for(int i = 0; i < RINGBUFF_LEN; i++) {
    iringbuff.Ringbuff[i] = 0;
  }
  iringbuff.Location = 0;
  iringbuff.Head = 0;
}

int Ringbuff_Write(Decode *s) {    
  if(iringbuff.Head <= 10) {
    iringbuff.Ringbuff[iringbuff.Head] = s->pc;
    iringbuff.Location = iringbuff.Head;
    iringbuff.Head++;
  }
  else {
    iringbuff.Head = 0;
    iringbuff.Ringbuff[iringbuff.Head] = s->pc;
    iringbuff.Location = iringbuff.Head;
    iringbuff.Head++;
  }
  return 0;
}

void Ringbuff_Print() {
  for(int i = 0; i < RINGBUFF_LEN; i++) {
    printf("                                0x""%lx\n", iringbuff.Ringbuff[i]);
  }
    printf("The PC of the last instruction: 0x""%lx\n", iringbuff.Ringbuff[iringbuff.Location]);
}
#endif


