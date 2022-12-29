#include <am.h>
#include <nemu.h>

void __am_timer_init() {
}

void __am_timer_uptime(AM_TIMER_UPTIME_T *uptime) {
    uptime->us = (((uint64_t)inl(RTC_ADDR + 4)) << 32) | inl(RTC_ADDR);
}

void __am_timer_rtc(AM_TIMER_RTC_T *rtc) {
  rtc->second = 16;
  rtc->minute = 51;
  rtc->hour   = 13;
  rtc->day    = 16;
  rtc->month  = 12;
  rtc->year   = 2022;
}
