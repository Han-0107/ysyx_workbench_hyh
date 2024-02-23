#include <am.h>

static inline uint32_t inl(uintptr_t addr) { return *(volatile uint32_t *)addr; }

#define DEVICE_BASE 0xa0000000
#define RTC_ADDR      (DEVICE_BASE + 0X00000048)

void __am_timer_init() {
}

void __am_timer_uptime(AM_TIMER_UPTIME_T *uptime) {
  uptime->us = (((uint64_t)inl(RTC_ADDR + 4)) << 32) | inl(RTC_ADDR);
}

void __am_timer_rtc(AM_TIMER_RTC_T *rtc) {
  rtc->second = 0;
  rtc->minute = 0;
  rtc->hour   = 0;
  rtc->day    = 0;
  rtc->month  = 0;
  rtc->year   = 1900;
}
