#define SDL_malloc  malloc
#define SDL_free    free
#define SDL_realloc realloc

#define SDL_STBIMAGE_IMPLEMENTATION
#include "SDL_stbimage.h"

SDL_Surface* IMG_Load_RW(SDL_RWops *src, int freesrc) {
  assert(src->type == RW_TYPE_MEM);
  assert(freesrc == 0);
  return NULL;
}

SDL_Surface* IMG_Load(const char *filename) {
  int fd = open(filename, 0, 0);
  // lseek returns the open_offset (SEEK_END which is size of the file/image)
  size_t sz = lseek(fd, 0, SEEK_END); // lseek to the end can find the size of the file
  unsigned char *buf = malloc(sz);
  lseek(fd, 0, SEEK_SET);             // reset the open_offset to 0
  read(fd, buf, sz);
  SDL_Surface *ret = STBIMG_LoadFromMemory(buf, sz);
  close(fd);
  free(buf);
  return ret;
}

int IMG_isPNG(SDL_RWops *src) {
  return 0;
}

SDL_Surface* IMG_LoadJPG_RW(SDL_RWops *src) {
  return IMG_Load_RW(src, 0);
}

char *IMG_GetError() {
  return "Navy does not support IMG_GetError()";
}
