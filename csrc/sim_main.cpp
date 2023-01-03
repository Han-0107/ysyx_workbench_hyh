#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <assert.h>
#include <unistd.h>
#include "Vnpc.h"
#include "Vnpc___024root.h"
#include "svdpi.h"
#include "Vnpc__Dpi.h"
#include <unistd.h>
#include "verilated_dpi.h"
#include <dlfcn.h>
#include <sys/time.h>

typedef long long ll;
#define COLOR_RED     "\33[1;31m"
#define COLOR_GREEN   "\33[1;32m"
#define COLOR_NONE    "\33[0m"
Vnpc *top = new Vnpc;
int status = 0;
int breakflag = 0;

// ********************************************Debug Tools******************************************** //
// #define MTRACE_ON
// #define ITRACE_ON
// #define DIFFTEST_ON

// ********************************************Devices******************************************** //
// Defines
#define DEVICE_BASE 0xa0000000
#define MMIO_BASE 0xa0000000

#define SERIAL_PORT   (DEVICE_BASE + 0x000003f8)
#define RTC_ADDR      (DEVICE_BASE + 0X00000048)

// timer
static uint64_t sec = 0;
static uint64_t sec_start = 0;

// ********************************************Functions******************************************** //
// Regs
uint64_t *cpu_gpr = NULL;
extern "C" void set_gpr_ptr(const svOpenArrayHandle r) {
  cpu_gpr = (uint64_t *)(((VerilatedDpiOpenVar*)r)->datap());
}

void dump_gpr() {
  int i;
  for (i = 0; i < 32; i++) {
    printf("gpr[%d] = %lx\n", i, cpu_gpr[i]);
  }
}

// Memory
#define MEM_BASE 0x80000000
#define MEM_SIZE 0x30000000
#define vaddr2paddr(addr) (pmem + addr - MEM_BASE)
static uint8_t pmem[MEM_SIZE];
uint8_t* cpu2mem(ll addr) { return pmem + (addr - MEM_BASE); }

static uint64_t paddr_read(uint8_t *addr, int len) {
    switch (len) {
        case 1:
            return *addr; break;
        case 2:
            return *(uint16_t *)addr; break;
        case 4:
            return *(uint32_t *)addr; break;
        case 8:
            return *(uint64_t *)addr; break;
        default:
            assert(false);
    }
}

extern "C" void pmem_read(ll raddr, ll *rdata)
{ 
  if (raddr < MEM_BASE | raddr > MEM_BASE + MEM_SIZE) 
    return;
  uint8_t *pt = cpu2mem(raddr) + 7;
  ll ret = 0;
  for (int i = 0; i < 8; i++) {
    ret = (ret << 8) | (*pt--);
  }
  *rdata = ret;

}

extern "C" void pmem_read_l(ll raddr, ll *rdata)
{ 
  #ifdef MTRACE_ON
    printf("read addr: 0x%llx\n", raddr);
  #endif

  // // timer
  // if(raddr == RTC_ADDR || raddr == RTC_ADDR + 4) {
  //   printf("time!\n");
  //   struct timeval time_day;
  //   gettimeofday(&time_day, NULL);
  //   if(sec_start == 0) {
  //     sec_start = time_day.tv_sec;
  //   }
  //   sec = time_day.tv_sec;
  //   uint64_t rtc = time_day.tv_usec + 1000000 * sec;
  //   if(raddr == RTC_ADDR) {
  //     *rdata = (rtc & 0x0000000000000000ffffffffffffffffl);
  //   }
  //   else if(raddr == RTC_ADDR + 4) {
  //     *rdata = (rtc >> 32);
  //   }
  // }

  if (raddr < MEM_BASE | raddr > MEM_BASE + MEM_SIZE) 
    return;
  uint8_t *pt = cpu2mem(raddr) + 7;
  ll ret = 0;
  for (int i = 0; i < 8; i++) {
    ret = (ret << 8) | (*pt--);
  }
  *rdata = ret;

}

extern "C" void pmem_write(ll waddr, ll wdata, char mask)
{
  if (waddr < MEM_BASE | waddr > MEM_BASE + MEM_SIZE) 
    return;
  uint8_t *pt = cpu2mem(waddr);
  for (int i = 0; i < 8; i++) {
    if (mask & 1) *pt = (wdata & 0xff);
    wdata >>= 8, mask >>= 1, pt++;
  }
    
}

extern "C" void pmem_write_s(ll waddr, ll wdata, char mask)
{ 
  #ifdef MTRACE_ON
    printf("write addr: 0x%llx\n", waddr);
  #endif

  // Serila port
  if(waddr == SERIAL_PORT) {
    putchar(wdata);
  }
  if (waddr < MEM_BASE | waddr > MEM_BASE + MEM_SIZE) 
    return;
  uint8_t *pt = cpu2mem(waddr);
  for (int i = 0; i < 8; i++) {
    if (mask & 1) *pt = (wdata & 0xff);
    wdata >>= 8, mask >>= 1, pt++;
  }
    
}

// Load images
uint64_t image_size = 0;

void load_image_test() {
    *(uint32_t*) (pmem)     = 0x00108013;      // addi      0x00108013
    *(uint32_t*) (pmem + 4) = 0x00108013;      // ebreak    0x00100073
    *(uint32_t*) (pmem + 8) = 0x00108013;      // ebreak    0x00100073
    *(uint32_t*) (pmem + 12) = 0x00100073;      // ebreak    0x00100073
    // *(uint32_t*) (pmem + 16) = 0x00108013;      // ebreak    0x00100073
    // *(uint32_t*) (pmem + 20) = 0x00108013;      // ebreak    0x00100073
    // *(uint32_t*) (pmem + 24) = 0x00108013;      // ebreak    0x00100073
    // *(uint32_t*) (pmem + 28) = 0x00108013;      // ebreak    0x00100073
    // *(uint32_t*) (pmem + 32) = 0x00108013;      // ebreak    0x00100073
    // *(uint32_t*) (pmem + 36) = 0x00100073;      // ebreak    0x00100073
}

void load_image() {
  char image_path[] = "/home/han/ysyx-workbench/npc/image.bin";
  FILE *stream = fopen(image_path, "rb");
  fseek(stream, 0, SEEK_END);
  image_size = ftell(stream);
  fseek(stream, 0, SEEK_SET);
  int ret = fread(pmem, image_size, 1, stream);
  fclose(stream);
}

// Break by accident
void ebreak() {
    // printf("ebreak!\n");
    printf("\033[1;32mHIT GOOD TRAP\033[0m");
    printf(" at pc: 0x%08lx\n", top->pc);
    delete top;
    exit(0);
}

void no_match() {
    // if(top->inst != 00000000) {
      printf("No matched inst:        %08x\n", uint32_t(top->inst));
      printf("\033[1;31mHIT BAD TRAP\033[0m");
      printf(" at pc: 0x%08lx\n", top->pc); 
      status = 1;
      delete top;
      exit(0);
    // }
}

// Execution of cpu
void exec_once() {
    top->clk = 0;
    top->eval();
    top->clk = 1;
    top->eval();
}

void cpu_exec(int N) {
    for(int i = 1; i <= N; i++) {
        exec_once();
    }
}

void reset() {
    top->rst = 1;
    exec_once();
    top->rst = 0;
}

// ********************************************DIFFTEST******************************************** //
// Definations about difftest
#ifdef DIFFTEST_ON
enum { DIFFTEST_TO_DUT, DIFFTEST_TO_REF };
void (*ref_difftest_memcpy)(uint32_t addr, void *buf, size_t n, bool direction) = NULL;
void (*ref_difftest_regcpy)(void *dut, bool direction) = NULL;
void (*ref_difftest_exec)(uint64_t n) = NULL;

uint64_t ref_regs[33];

void init_difftest() {
  char ref_so_file[] = "/home/han/ysyx-workbench/nemu/build/riscv64-nemu-interpreter-so";

  void *handle;
  handle = dlopen(ref_so_file, RTLD_LAZY);
  assert(handle);

  ref_difftest_memcpy = (void (*)(uint32_t addr, void *buf, size_t n, bool direction))(dlsym(handle, "difftest_memcpy"));
  assert(ref_difftest_memcpy);

  ref_difftest_regcpy = (void (*)(void *dut, bool direction))(dlsym(handle, "difftest_regcpy"));
  assert(ref_difftest_regcpy);

  ref_difftest_exec = (void (*)(uint64_t n))(dlsym(handle, "difftest_exec"));
  assert(ref_difftest_exec);

  void (*ref_difftest_init)() = (void (*)())(dlsym(handle, "difftest_init"));
  assert(ref_difftest_init);

  ref_difftest_init();
  ref_difftest_memcpy(MEM_BASE, pmem, image_size, DIFFTEST_TO_REF);
}

void checkregs(uint64_t *ref_regs) {
  cpu_gpr[32] = top->pc;
  for (int i = 0; i < 32; ++i) {
    if (ref_regs[i] != cpu_gpr[i]) {
      status = 1;
      printf("Error: Difftest failed at reg %d, pc = 0x%016lx\n", i, (cpu_gpr[32] - 0x80000004));
      for (int j = 0; j < 32; ++j) {
        if (cpu_gpr[j] != ref_regs[j]) {printf(COLOR_RED);}
        printf("reg %02d: dut = 0x%016lx, ref = 0x%016lx\n", j, cpu_gpr[j], ref_regs[j]);
        if (cpu_gpr[j] != ref_regs[j]) printf(COLOR_NONE);
      }
      printf("\033[1;31mHIT BAD TRAP\033[0m\n");
      breakflag = 1;
      status = 1;
      break;
    }
  }
}

void checkpc(uint64_t *ref_regs) {
  if(top->pc != ref_regs[32]) {
      printf("Error: Difftest failed");
      printf(COLOR_RED);
      printf("PC: dut = 0x%016lx, ref = 0x%016lx\n", top->pc, ref_regs[32]);
      printf("\033[1;31mHIT BAD TRAP\033[0m\n");
      breakflag = 1;
      status = 1;
  }
}

void difftest_exec_once() {
  ref_difftest_exec(1);
  ref_difftest_regcpy(ref_regs, DIFFTEST_TO_DUT);
  checkregs(ref_regs);
  checkpc(ref_regs);
}
#endif

int main() {
    load_image();
    reset();   
    reset(); 
    printf("\033[1;32mProgram Begin\033[0m\n");
    if(top->pc != 0x80000000) {
      assert(0);
      status = 1;
    }
    #ifndef DIFFTEST_ON
    while(1) {
      #ifdef ITRACE_ON
        printf("PC: 0x%lx    ", top->pc);
        printf("INST: %08x\n", uint32_t(top->inst));      
      #endif
        cpu_exec(1);
      #ifdef ITRACE_ON
        // dump_gpr(); 
      #endif
        // dump_gpr();
    }
    #endif

    #ifdef DIFFTEST_ON
      init_difftest();
      while(1) {
          cpu_exec(1);
          difftest_exec_once();
          if(breakflag == 1) break;
      }
    #endif
    return status;
}
