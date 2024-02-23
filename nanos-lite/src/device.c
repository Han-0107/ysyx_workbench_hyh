#include <common.h>

#if defined(MULTIPROGRAM) && !defined(TIME_SHARING)
# define MULTIPROGRAM_YIELD() yield()
#else
# define MULTIPROGRAM_YIELD()
#endif

#define NAME(key) \
  [AM_KEY_##key] = #key,

static const char *keyname[256] __attribute__((used)) = {
  [AM_KEY_NONE] = "NONE",
  AM_KEYS(NAME)
};

size_t serial_write(const void *buf, size_t offset, size_t len) {
  for (int i = 0; i < len; ++i) {
    putch(*(char *)(buf + i));
  }
  return len;
}

size_t events_read(void *buf, size_t offset, size_t len) {
  AM_INPUT_KEYBRD_T kbd;
  ioe_read(AM_INPUT_KEYBRD, &kbd);
  if (kbd.keycode == 0) return 0;
  if (kbd.keydown == true) {
    len = snprintf(buf, len, "kd %s\n", keyname[kbd.keycode]);
  } 
  else {
    len = snprintf(buf, len, "ku %s\n", keyname[kbd.keycode]);
  }
  return len;
}

size_t dispinfo_read(void *buf, size_t offset, size_t len) {
  AM_GPU_CONFIG_T cfg;
  ioe_read(AM_GPU_CONFIG, &cfg);
  return snprintf(buf, len, "WIDTH:%d\nHEIGHT:%d\n", cfg.width, cfg.height);
}

size_t fb_write(const void *buf, size_t offset, size_t len) {
  offset /= 4, len /= 4;
  // printf("== offset: %d, len: %d ==\n", offset, len);
  // size of screen
  AM_GPU_CONFIG_T cfg;
  ioe_read(AM_GPU_CONFIG, &cfg);
  // fill
  AM_GPU_FBDRAW_T ctl;
  ctl.h = ctl.w = 0;
  int used = 0;    // number of pixels
  // (x, y) -> (width, height)
  ctl.x = offset % cfg.width, ctl.y = offset / cfg.width;
  // printf("%d %d\n", ctl.x, ctl.y);
  if (len >= cfg.width) {
    ctl.h = len / cfg.width, ctl.w = cfg.width;
    ctl.pixels = (void *)buf;
    ctl.sync = true;
    ioe_write(AM_GPU_FBDRAW, &ctl);
    used += ctl.h * ctl.w * 4;
  }
  ctl.x += ctl.h;
  if (len % cfg.width != 0) {
    ctl.h = 1, ctl.w = len % cfg.width;
    ctl.pixels = (void *)(buf + used);
    // ctl.sync = true;
    ioe_write(AM_GPU_FBDRAW, &ctl);
  }
  return len;
}

void init_device() {
  Log("Initializing devices...");
  ioe_init();
}
