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

#include "sdb.h"
#include <stdlib.h>

#define NR_WP 32

typedef struct watchpoint {
  int NO;
  struct watchpoint *next;

  /* TODO: Add more members if necessary */
  uint64_t value;
  // uint64_t new_value;
  char exp[32];
} WP;

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
  }

  head = NULL;
  free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */

WP* new_wp() {
  if(free_ == NULL)
    assert(0);
  WP* tmp = free_;
  free_ = free_->next;
  if(head != NULL)
    tmp->next = head;
  else
    tmp->next = NULL;
  head = tmp;
  return tmp;
}

void free_wp(int num) {
  WP *p, *q;

  q = NULL;
  p = head;
  while(p != NULL && p->NO != num) {
    q = p;
    p = p->next;
  }
  if(p == NULL) 
    assert(0);
  if(q == NULL) {
    head = head->next;
    p->value = 0;
    memset(p->exp, 0, sizeof(p->exp));
    p->next = free_;
    free_ = p;
  }
  else {
    q->next = p->next;
    p->value = 0;
    memset(p->exp, 0, sizeof(p->exp));
    p->next = free_;
    free_ = p;
  }
  printf("Free the watchpoint NO.%d\n", p->NO);
  return;
}

void print_wp() {
  WP* tmp = head;
  printf("NUM\t VALUE\t\t CONTENT\n");
  while(tmp) {
    printf("%4d\t0x%lx\t\t%s\n", tmp->NO, tmp->value, tmp->exp);
    tmp = tmp->next;
  }
  return;
}

// int judge_wp() {
//   WP* p;
//   bool success;

//   p = head;
//   if(p == NULL)
//     return 0;
//   while(p) {
//     p->new_value = expr(p->exp, &success);
//     if(p->new_value != p->value)
//       return -1;
//     p = p->next;
//   }
//   return 0;
// }

int add_wp(char *str, bool *success) {
  WP* wp = new_wp();
  strcpy(wp->exp, str);
  wp->value = expr(str, success);
  return wp->NO;
}
