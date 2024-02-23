#include <NDL.h>
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define keyname(k) #k,

static const char *keyname[] = {
  "NONE",
  _KEYS(keyname)
};

#define NUMBER_OF_KEYS 83
#define EVENT_BUF_LENGTH 64
char buf[EVENT_BUF_LENGTH];
uint8_t status[NUMBER_OF_KEYS];

int SDL_PushEvent(SDL_Event *ev) {
  printf("Unimplemented function: SDL_PushEvent\n");
  while (1);
  return 0;
}

int SDL_PollEvent(SDL_Event *ev) {
  if (NDL_PollEvent(buf, EVENT_BUF_LENGTH) == 0) {  // 如果当前没有任何事件, 就会立即返回
    ev->type = SDL_KEYUP;
    ev->key.keysym.sym = SDLK_NONE;
    return 0;
  }
  if (buf[0] == 'k') {
    int code = 0;
    for (int i = 0; i < 83; ++i) {
      if (strncmp(buf + 3, keyname[i], strlen(buf + 3) - 1) == 0) {
        code = i;
        break;
      }
    }
    if (buf[1] == 'd') {
      ev->type = SDL_KEYDOWN;
      ev->key.keysym.sym = code;
      status[code] = 1;
      // printf("SDL_PollEvent: Key Down %d\n", code);
    } 
    else if (buf[1] == 'u') {
      ev->type = SDL_KEYUP;
      ev->key.keysym.sym = code;
      status[code] = 0;
      // printf("SDL_PollEvent: Key Up %d\n", code);
    }
    return 1;
  }
  printf("Should not reach here\n");
  while (1);
}

int SDL_WaitEvent(SDL_Event *event) {
  while (SDL_PollEvent(event) == 0);
  return 1;
}

int SDL_PeepEvents(SDL_Event *ev, int numevents, int action, uint32_t mask) {
  printf("Unimplemented function: SDL_PeepEvents\n");
  while (1);
  return 0;
}

uint8_t* SDL_GetKeyState(int *numkeys) {
  return status;
}
