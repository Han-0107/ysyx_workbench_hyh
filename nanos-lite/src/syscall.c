#include <common.h>
#include "syscall.h"
#include <sys/time.h>
#include "fs.h"

int fs_open(const char *pathname, int flags, int mode);
size_t fs_read(int fd, void *buf, size_t len);
size_t fs_write(int fd, const void *buf, size_t len);
size_t fs_lseek(int fd, size_t offset, int whence);
int fs_close(int fd);
size_t write(int fd, intptr_t buf, size_t count);

void do_syscall(Context *c) {
  int us = 0;
  switch (c->GPR1) {
    case SYS_exit:
      // printf("[Strace - do_syscall] SYS_exit.\n");
      halt(0);
      break;
    case SYS_yield:
      // printf("[Strace - do_syscall] SYS_yield.\n");
      yield();
      c->GPRx = 0;
      break;
    case SYS_brk:
      // printf("[Strace - do_syscall] SYS_brk\n");
      c->GPRx = 0;
      break;
    case SYS_open:
      // printf("[Strace - do_syscall] SYS_open\n");
      c->GPRx = fs_open((const char *)c->GPR2, c->GPR3, c->GPR4);
      break;
    case SYS_read:
      // printf("[Strace - do_syscall] SYS_read\n");
      c->GPRx = fs_read(c->GPR2, (void *)c->GPR3, c->GPR4);
      break;
    case SYS_write:
      // printf("[Strace - do_syscall] SYS_write\n");
      c->GPRx = fs_write(c->GPR2, (void *)c->GPR3, c->GPR4);
      break;
    case SYS_lseek:
      // printf("[Strace - do_syscall] SYS_lseek\n");
      c->GPRx = fs_lseek(c->GPR2, c->GPR3, c->GPR4);
      break;
    case SYS_close:
      // printf("[Strace - do_syscall] SYS_close\n");
      c->GPRx = fs_close(c->GPR2);
      break;
    case SYS_gettimeofday:
      us = io_read(AM_TIMER_UPTIME).us;
      ((struct timeval *) c->GPR2)->tv_usec = us % 1000000;
      ((struct timeval *) c->GPR2)->tv_sec = us / 1000000;
      // TODO: bugs occurs when playing flappy bird, so comments here.
      // ((struct timezone *)c->GPR3)->tz_minuteswest = -480; // China (to be edited if it has error)
      // ((struct timezone *)c->GPR3)->tz_dsttime = 0;
      c->GPRx = 0;
      break;
    default: panic("Unhandled syscall ID = %d", c->GPR1);
  }
}
