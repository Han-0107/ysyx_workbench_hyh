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

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

word_t vaddr_read(vaddr_t addr, int len);

enum {
  TK_NOTYPE = 256, TK_EQ, TK_NEQ, TK_AND, TK_OR, TK_NOT, TK_REG, TK_NUM, TK_HNUM, TK_DEREF     
 
  /* TODO: Add more token types */
};

static struct rule {
  const char *regex;
  int token_type;
} rules[] = {

  /* TODO: Add more rules.
   * Pay attention to the precedence level of different rules.
   */

  {" +", TK_NOTYPE},          // spaces
  {"\\(", '('},               // left parenthesis
  {"\\)", ')'},               // right parenthesis
  {"\\+", '+'},               // plus
  {"\\-", '-'},               // minus
  {"\\*", '*'},               // multiply
  {"\\/", '/'},               // divide

  {"==", TK_EQ},              // equal
  {"\\!=", TK_NEQ},           // not equal
  {"\\|\\|", TK_OR},          // or  
  {"\\&\\&", TK_AND},         // and
  {"\\!", TK_NOT},            // not

  {"0[xX][0-9a-fA-F]{1,8}", TK_HNUM},    // hex numbers (this must be front of 'numbers'!)
  {"[0-9]{1,10}", TK_NUM},               // numbers
  {"\\$[\\$a-zA-Z][0-9a-zA-Z]+", TK_REG}  // registers
};

#define NR_REGEX ARRLEN(rules)

static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i ++) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0) {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}

typedef struct token {
  int type;
  char str[32];
} Token;

static Token tokens[32] __attribute__((used)) = {};
static int nr_token __attribute__((used))  = 0;

static bool make_token(char *e) {
  int position = 0;
  int i;
  regmatch_t pmatch;

  nr_token = 0;

  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i ++) {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
            i, rules[i].regex, position, substr_len, substr_len, substr_start);

        position += substr_len;

        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */

        switch (rules[i].token_type) {
            case TK_EQ: 
                tokens[nr_token].type = TK_EQ;
                strcpy(tokens[nr_token].str, "==");break;
            case TK_NEQ:
                tokens[nr_token].type = TK_NEQ;
                strcpy(tokens[nr_token].str, "!=");break;
            case TK_AND: 
                tokens[nr_token].type = TK_AND;
                strcpy(tokens[nr_token].str, "&&");break;
            case TK_OR: 
                tokens[nr_token].type = TK_OR;
                strcpy(tokens[nr_token].str, "||");break;
            case TK_NOT: 
                tokens[nr_token].type = TK_NOT;
                strcpy(tokens[nr_token].str, "!");break;
            case 40:
                tokens[nr_token].type = 40;break;            //'('
            case 41:
                tokens[nr_token].type = 41;break;            //')'
            case 42:
                tokens[nr_token].type = 42;break;            //'*'
            case 43:
                tokens[nr_token].type = 43;break;            //'+'
            case 45:
                tokens[nr_token].type = 45;break;            //'-'
            case 47:
                tokens[nr_token].type = 47;break;            //'/'                                                                              
            case TK_HNUM: 
                tokens[nr_token].type = TK_HNUM;
                strncpy(tokens[nr_token].str, &e[position-substr_len], substr_len);break;
            case TK_NUM:
                tokens[nr_token].type = TK_NUM;
                strncpy(tokens[nr_token].str, &e[position-substr_len], substr_len);break;                
            case TK_REG: 
                tokens[nr_token].type = TK_REG;
                strncpy(tokens[nr_token].str, &e[position-substr_len], substr_len);break;
          default: 
                nr_token--;
                break;
        }
        nr_token++;
        break;
      }
    }

    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }
  nr_token--;
  return true;
}

bool check_parentheses(int p, int q) {
  int flag = 0;
  int par_l = 0;

  if(tokens[p].type == 40) {               // The first token should be '('
    par_l++;
    for(int i = p+1; i <= q; i++) {
      if(tokens[i].type == 40) {          // If the program meets another '(' ,the left parentheses will require one more ')'
        par_l++;
      }
      else if(tokens[i].type == 41) {     // If the program meets a ')', the left parentheses will require one less ')'
        par_l--;

        if(par_l == 0 && i != q)
          flag = 1;
        if(par_l < 0) 
          assert(0);
      }
    }
    if(par_l == 0 && tokens[q].type == 41 && flag != 1) {
      return true;
    }
    else if(par_l == 0)
      return false;
    else
      assert(0);
  }
  else
      return false;
}

static int take_main_operator(int p, int q) {
  int op_site = p;
  int j = p;
  int r = 0;

  for(; j <= q; j++) {
    if(tokens[j].type < 262 && tokens[j].type != '!') {
      if(tokens[j].type == 40) {
        r++;
        for(j = j + 1; tokens[j].type != 41 || r != 1;j++) {
          if(tokens[j].type == 40) r++;
          if(tokens[j].type == 41) r--;
        }
        r = 0;
      }
      else if(tokens[j].type == TK_OR) op_site = j;
      else if((tokens[j].type == TK_AND) && (tokens[op_site].type < 260 || tokens[op_site].type >= 262)) op_site = j;
      else if((tokens[j].type == TK_NEQ) && (tokens[op_site].type < 259 || tokens[op_site].type >= 262)) op_site = j;
      else if((tokens[j].type == TK_EQ) && (tokens[op_site].type < 258 || tokens[op_site].type >= 262)) op_site = j;
      else if((tokens[j].type == '+') && (tokens[op_site].type < 256 || tokens[op_site].type >= 261)) op_site = j;
      else if((tokens[j].type == '-') && (j == p || tokens[j - 1].type >= 256 || tokens[j - 1].type == ')') && (tokens[op_site].type < 256 || tokens[op_site].type >= 261)) op_site = j;
      else if((tokens[j].type == '/') && (tokens[op_site].type >= 261 || tokens[op_site].type == '(' || tokens[op_site].type == '*' || tokens[op_site].type == '/')) op_site = j;
      else if(tokens[j].type == '*' && (j == p || (tokens[j - 1].type >= 256 || tokens[j - 1].type == ')')) && (tokens[op_site].type >= 261 || tokens[op_site].type == '(' || tokens[op_site].type == '*' || tokens[op_site].type == '/')) op_site = j;
    }
  }
  return op_site;
}

static int eval(int p, int q) {
  int i = 0;

  if (p > q) {
      /* Bad expression */
    assert(0);
  }
  else if (p == q) {
    /* Single token.
     * For now this token should be a number.
     * Return the value of the number.
     */

    // The 'Single token' means there is no expression for us to calculate.
    // What we need to do is take the value of what the number means.
    if(tokens[p].type == TK_HNUM) {
      sscanf(tokens[p].str, "%x", &i);
      return i;
    }
    else if(tokens[p].type == TK_NUM) {
      sscanf(tokens[p].str, "%d", &i);
      return i;
    }
    else if(tokens[p].type == TK_REG) {
      strcpy(tokens[p].str,tokens[p].str+1);
      i = isa_reg_str2val(tokens[p].str, true);
      return i;
    }
    else {
      assert(0);
    }
  }
  else if (check_parentheses(p, q) == true) {
    /* The expression is surrounded by a matched pair of parentheses.
     * If that is the case, just throw away the parentheses.
     */
    return eval(p + 1, q - 1);
  }
  else {
    /* We should do more things here. */
    int op;
    u_int64_t val1, val2;

    if(((q-p == 1) || (tokens[p + 1].type == 40 && tokens[q].type == 41)) && tokens[p].type == '!') {
      i = eval(p + 1, q);
      return !i;
    }

    if(((q-p == 1) || (tokens[p + 1].type == 40 && tokens[q].type == 41)) && tokens[p].type == '*') {
      return vaddr_read(eval(p + 1, q), 4);
    }

    op = take_main_operator(p, q);
    val1 = eval(p, op - 1);
    val2 = eval(op + 1, q);

    switch(tokens[op].type) {
        case 42: return (val1 * val2);
        case 43: return (val1 + val2);
        case 45: return (val1 - val2);
        case 47: return (val1 / val2);
        case TK_AND: return (val1 && val2);
        case TK_EQ: return (val1 == val2);
        case TK_NEQ: return (val1 != val2);
        case TK_OR: return (val1 || val2);
        default: assert(0);
    }

  }
  return 0;

}

word_t expr(char *e, bool *success) {
  int ans;

  if (!make_token(e)) {
    *success = false;
    return 0;
  }
  /* TODO: Insert codes to evaluate the expression. */
  for(int i = 0; i < nr_token; i++) {
    if(tokens[i].type == '*' && (i == 0 || tokens[i - 1].type == TK_NOTYPE || tokens[i - 1].type == '+' || tokens[i - 1].type == '-' || tokens[i - 1].type == '*' || tokens[i - 1].type == '/'))
    tokens[i].type = TK_DEREF;
  }
  ans = eval(0, nr_token);
  return ans;
}
