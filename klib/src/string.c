#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  unsigned int len = 0;
  while((*s++) != '\0') { len++; }
  return len;
}

char *strcpy(char *dst, const char *src) {
  if(dst == NULL || src == NULL)
    return NULL;
  if(dst == src)
    return dst;
  char *tempdst = dst;
  while((*dst++ = *src++) != '\0');
  return tempdst;
}

char *strncpy(char *dst, const char *src, size_t n) {
  assert((dst != NULL) && (src != NULL));
  char *addr = dst;
  while(n-->0)
    *dst++ = *src++;
  return addr;
}

char *strcat(char *dst, const char *src) {
  char *addr = dst;
  assert((dst != NULL) && (src != NULL));
  while(*dst) {
    dst++;
  }
  while((*dst++ = *src++) != '\0') {
    NULL;
  }
  return addr;
}

int strcmp(const char *s1, const char *s2) {
  int ret = 0;
  while(!(ret = *s1 - *s2) && *s2) {
    ++s1;
    ++s2;
  }
  if(ret < 0) {
    ret = -1;
  }
  else if(ret > 0) {
    ret = 1;
  }
  else {
    ret = 0;
  }
  return ret;
}

int strncmp(const char *s1, const char *s2, size_t n) {
  if(!n)
   return 0;
  while(--n && *s1 && *s1 == *s2) {
    s1++;
    s2++;
  }
  return (*s1 - *s2);
}

void *memset(void *s, int c, size_t n) {
  size_t cnt = 0;
  unsigned char *schar = s;
  while(cnt < n) {
    *schar++ = (unsigned char) c;
    cnt++;
  }
  return s;
}

void *memmove(void *dst, const void *src, size_t n) {
  void*ret = dst;
  if(dst <= src || (char*)dst >= ((char*)src + n)) {
    while(n--) {
      *(char*)dst = *(char*)src;
      dst = (char*)dst + 1;
      src = (char*)src + 1;
    }
  }
  else {
    dst = (char*)dst + n - 1;
    src = (char*)src + n - 1;
    while(n--) {
      *(char*)dst = *(char*)src;
      dst = (char*)dst - 1;
      src = (char*)src - 1;
    }
  }
  return ret;
}

void *memcpy(void *out, const void *in, size_t n) {
  assert(out && in);
  void* ret = out;
  while(n--) {
    *(char*)out = *(char*)in;
    out = (char*)out + 1;
    in = (char*)in + 1;
  }
  return ret;
}

int memcmp(const void *s1, const void *s2, size_t n) {
  const unsigned char *su1, *su2;
  int res = 0;
  for(su1 = s1, su2 = s2; 0 < n; ++su1, ++su2, n--)
    if((res = *su1 - *su2) != 0)
      break;
  return res;
}

#endif
