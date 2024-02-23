#include <am.h>
#include <nemu.h>
#include <amdev.h>

#define SYNC_ADDR (VGACTL_ADDR + 4)
#define FB_ADDR         (MMIO_BASE   + 0x1000000)
#define VGACTL_ADDR     (DEVICE_BASE + 0x0000100)

 void __am_gpu_init() {
 }

void __am_gpu_config(AM_GPU_CONFIG_T *cfg) {
  int height = inw(VGACTL_ADDR);
  int width = inw(VGACTL_ADDR + 2);
  *cfg = (AM_GPU_CONFIG_T) {
    .present = true, .has_accel = false,
    .width = width, .height = height,
    .vmemsz = width * height * sizeof(uint32_t)
  };
}

void __am_gpu_fbdraw(AM_GPU_FBDRAW_T *ctl) {
  int width = inw(VGACTL_ADDR + 2);
  for (int i = 0; i < ctl->h; ++i) {
    for (int j = 0; j < ctl->w; ++j) {
      outl(FB_ADDR + (width * (ctl->y + i) + (ctl->x + j)) * sizeof(uint32_t), ((uint32_t*)ctl->pixels)[i * ctl->w + j]);
    }
  }
  if (ctl->sync) {
    outl(SYNC_ADDR, 1);
  }
}

void __am_gpu_status(AM_GPU_STATUS_T *status) {
  status->ready = true;
}
