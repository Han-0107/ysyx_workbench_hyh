#include <common.h>

void do_syscall(Context *c);

static Context* do_event(Event e, Context* c) {
  switch (e.event) {
    case 1: // EVENT_YIELD
      // printf("ETRACE：Event yield\n"); 
      break;
    case 2: // EVENT_SYSCALL
      // printf("ETRACE：Event syscall\n"); 
      do_syscall(c);
      break;
    case 4: // EVENT_ERROR
      // printf("ETRACE：Event error\n"); 
      panic("event error\n");
      break;
    default: panic("Unhandled event ID = %d", e.event);
  }

  return c;
}

void init_irq(void) {
  Log("Initializing interrupt/exception handler...");
  cte_init(do_event);
}
