#include <unistd.h>
#include <stdio.h>
#include <NDL.h>

int main() {
  int num = 0;
  long preus = NDL_GetTicks();
  while (1) {
    long us = NDL_GetTicks();
    if (us - preus >= 500) {
      printf("0.5 secs has passed for %d times\n", num++);
      preus = us;
    }
  }
  return 0;
}
