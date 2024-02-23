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

#include <isa.h>
#include "local-include/reg.h"

const char *regs[] = {
  "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
  "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
  "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
  "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};

void isa_reg_display() {
  for(int i = 0; i < 32; i++) {
    printf("Register = %s, value = %lx\n", regs[i], cpu.gpr[i]);
    // printf("--------------------------\n");
  }
}

void show_image() {
printf("                                                            !88~                           \n");        
printf("                                                 8           88886                         \n");         
printf("                                                .88          8888888!                      \n");         
printf("                                                888z   !8888888888                         \n");         
printf("                               !868888         888888888888888881                          \n");         
printf("            u888   8888888888888888888;       88888888888     88                           \n");         
printf("           8888888888888888888883!            888888-        18888888      u333388888      \n");         
printf("            88888888888888888                  88          -8888 888       8888888888      \n");         
printf("             888888888888888                               888888888             8888      \n");         
printf("              o888888888^                                 888888888              8888      \n");         
printf("                 3.                                      88888888888             8888      \n");         
printf("                                                          888888;                8888      \n");         
printf("                                                         8888888888i             8888      \n");         
printf("                                                        68888888888888         u  88 38    \n");         
printf("                                                                               u  88 38    \n");         
printf("                                                    8a         8               u  88 38    \n");        
printf("                                                   8888       88               u  88 38    \n");         
printf("                                                   88888  .888888888888        8  88 38    \n");         
printf("                                                 8888888888888888888           8  88 38    \n");         
printf("                                            n8888888888888888                  8  88 38    \n");         
printf("                         1888888888886         ^8888888  88                    8  88 38    \n");         
printf("            388888888888888888888888888                                        8  88 38    \n");         
printf("              8888888888888888888888888                              ;         8  88 38    \n");         
printf("               -888888888888888                    13    .3333z n3333333333    8  88 38    \n");         
printf("                 88888888888                      33       33333333333333333   8  88 38    \n");         
printf("                        8+                       333         3333333.          8  88 38    \n");         
printf("                      ;                         333z  333i     3333333         8  88 38    \n");         
printf("                                              3333    3333333333333333        8  88 38     \n");       
printf("                                              33333       -3333333+            8  88 38    \n");         
printf("                                              33333                            8  88 38    \n");         
printf("                          88 88                333                             8  88 38    \n");         
printf("                          88 88                                                8  88 38    \n");         
printf("                          88 8888888888888888888888888888888888888888888888888888888 38    \n");         
printf("                          88 8888868888888888888888888888888888888888888888888888888 38    \n");         
printf("                          ~  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  ~    \n");  
}

word_t isa_reg_str2val(const char *s, bool success) {
  for(int i = 0; i < 32; i++) {
    if(strcmp(regs[i], s) == 0) {
      success = true;
      return cpu.gpr[i];
    }
  }
  success = false;
  return 0;
}
