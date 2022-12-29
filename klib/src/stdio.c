#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int vprintf(const char *fmt, va_list ap) {
  char out[4096];
  int cnt = vsprintf(out, fmt, ap);
  putstr(out);
  return cnt;
}

int printf(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  int siz = vprintf(fmt, args);
  va_end(args);
  return siz;
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  int cnt = 0;
  for (int i = 0; fmt[i]; i++)
  {
    if (fmt[i] != '%') {
      out[cnt++] = fmt[i];
      continue;
    }
    int num = 0, num_b_cnt = 0;
    int num_b[20] = {0};
    char *str = NULL;
    char chr;
    switch (fmt[i + 1]) {
    case 'd':
      num_b_cnt = 0;
      num = va_arg(ap, int);
      if (num == 0)
        num_b[++num_b_cnt] = 0;
      else if (num < 0)
        out[cnt++] = '-', num = -num;
      while (num != 0) {
        num_b[++num_b_cnt] = num % 10;
        num /= 10;
      }
      for (int i = num_b_cnt; i >= 1; i--)
        out[cnt++] = (char)(num_b[i] + '0');
      break;

    case 's':
      str = va_arg(ap, char *);
      for (int i = 0; str[i]; i++)
        out[cnt++] = str[i];
      break;

    case 'c':
      chr = va_arg(ap, int);
      out[cnt++] = chr;
      break;

    default: break;
    }
    i++;
  }
  out[cnt++] = '\0';
  return cnt;
}

int sprintf(char *out, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  int siz = vsprintf(out, fmt, args);
  va_end(args);
  return siz;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif