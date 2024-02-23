#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static int evtdev = -1;
static int fbdev = -1;
static int screen_w = 0, screen_h = 0;
static int canvas_w = 0, canvas_h = 0;
static int center_w = 0, center_h = 0;

static uint32_t base_ticks = 0;

uint32_t NDL_GetTicks() {
  struct timeval tv;
  struct timezone tz;
  gettimeofday(&tv, &tz);
  return tv.tv_sec * 1000 + tv.tv_usec / 1000 - base_ticks; // 输出us
}

int NDL_PollEvent(char *buf, int len) {
  int fd = open("/dev/events", 0, 0);
  int sz = read(fd, buf, len);
  // if (sz != 0) printf("\"%s\" with %d\n", buf, sz);
  return sz != 0;
}
void NDL_OpenCanvas(int *w, int *h) {
  if (getenv("NWM_APP")) {
    int fbctl = 4;
    fbdev = 5;
    screen_w = *w; screen_h = *h;
    char buf[64];
    int len = sprintf(buf, "%d %d", screen_w, screen_h);
    // let NWM resize the window and create the frame buffer
    write(fbctl, buf, len);
    while (1) {
      // 3 = evtdev
      int nread = read(3, buf, sizeof(buf) - 1);
      if (nread <= 0) continue;
      buf[nread] = '\0';
      if (strcmp(buf, "mmap ok") == 0) break;
    }
    close(fbctl);
  }
  // printf("%d %d\n", screen_w, *w);
  // printf("%d %d\n", screen_h, *h);
  if (*w == 0) *w = screen_w;
  if (*h == 0) *h = screen_h;
  assert(1 <= *w && *w <= screen_w);
  assert(1 <= *h && *h <= screen_h);
  canvas_w = *w;
  canvas_h = *h;
  center_w = screen_w / 2 - canvas_w / 2;
  center_h = screen_h / 2 - canvas_h / 2;
  // printf("%d %d\n", center_h, center_w);
}

void NDL_DrawRect(uint32_t *pixels, int x, int y, int w, int h) {
  int fd = open("/dev/fb", 0, 0);
  // printf("%d\n", fd);
  for (int i = 0; i < h; ++i) {
    // printf("write %d\n", i);
    lseek(fd, ((center_h + y + i) * screen_w + center_w + x) * 4, SEEK_SET);
    write(fd, pixels + i * w, w * 4);
  }
}

void NDL_OpenAudio(int freq, int channels, int samples) {
}

void NDL_CloseAudio() {
}

int NDL_PlayAudio(void *buf, int len) {
  return 0;
}

int NDL_QueryAudio() {
  return 0;
}

int NDL_Init(uint32_t flags) {
  if (getenv("NWM_APP")) {
    evtdev = 3;
  }
  int fd;
  // fetch size of screen
  fd = open("/proc/dispinfo", 0, 0);
  char buf[64];
  read(fd, buf, 64);
  int len = strlen(buf), flag = 1;
  for (int i = 0; i < len; ++i) {
    if ('0' <= buf[i] && buf[i] <= '9') {
      if (!flag) screen_w = screen_w * 10 + buf[i] - '0';
      else screen_h = screen_h * 10 + buf[i] - '0';
    } else if (buf[i] == ':') flag ^= 1;
  }
  // get base ticks
  struct timeval tv;
  struct timezone tz;
  gettimeofday(&tv, &tz);
  base_ticks = tv.tv_sec * 1000 + tv.tv_usec / 1000;
  return 0;
}

void NDL_Quit() {
}
