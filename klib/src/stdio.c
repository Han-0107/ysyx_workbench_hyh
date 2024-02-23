#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

typedef long long ll;

inline bool typechar(size_t *rem) {
  --(*rem);
  return rem == 0;
}

char* num2str(char *str, ll num, ll base, size_t *rem) {
  char tmp[32];
  if (num < 0) {
    *str++ = '-';
    num = -num;
    if (typechar(rem)) return str;
  }
  int len = 0;
  if (num == 0) tmp[len++] = 0;
  else while (num) {
    tmp[len++] = num % base;
    num = num / base;
  }
  while (len-- > 0) {
    if (tmp[len] < 10) *str++ = tmp[len] + '0';
    else *str++ = tmp[len] - 10 + 'A';
    if (typechar(rem)) return str;
  }
  return str;
}

int printf(const char *fmt, ...) {
  int n;
  char buf[8192];
  va_list args;
  va_start(args, fmt);
  n = vsprintf(buf, fmt, args);
  va_end(args);
  putstr(buf);
  return n;
}

int sprintf(char *out, const char *fmt, ...) {
  int n;
  va_list args;
  va_start(args, fmt);
  n = vsprintf(out, fmt, args);
  va_end(args);
  return n;
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  size_t inf = 0x3f3f3f3f;
  char *s;
  char *str;
  for (str = out; *fmt; fmt++) {
    if (*fmt != '%') {
      *str++ = *fmt;
      continue;
    }
    fmt++;
    switch (*fmt) {
      case 'c':
        *str++ = va_arg(ap, int);
        break;
      case 'd':
        // cannot handle %02d etc. maybe fix future.
        str = num2str(str, va_arg(ap, ll), 10, &inf);
        break;
      case 'p':
        str = num2str(str, va_arg(ap, ll), 16, &inf);
        break;
      case 's':
        s = va_arg(ap, char *);
        while (*s) *str++ = *s++;
        break;
      default:
        if (*fmt != '%') *str++ = '%';
        if (*fmt) *str++ = *fmt;
        else fmt--;
        break;
    }
  }
  *str = '\0';
  return str - out;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  n = vsnprintf(out, n, fmt, args);
  va_end(args);
  return n;
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  char *s;
  char *str;
  for (str = out; *fmt; fmt++) {
    if (*fmt != '%') {
      *str++ = *fmt;
      continue;
    }
    fmt++;
    switch (*fmt) {
      case 'c':
        *str++ = va_arg(ap, int);
        if (typechar(&n)) break;
        break;
      case 'd':
        // cannot handle %02d etc. maybe fix future.
        str = num2str(str, va_arg(ap, ll), 10, &n);
        if (n == 0) break;
        break;
      case 'p':
        str = num2str(str, va_arg(ap, ll), 16, &n);
        if (n == 0) break;
        break;
      case 's':
        s = va_arg(ap, char *);
        while (*s) {
          *str++ = *s++;
          if (typechar(&n)) break;
        }
        if (n == 0) break;
        break;
      default:
        if (*fmt != '%') {
          *str++ = '%';
          if (typechar(&n)) break;
        }
        if (*fmt) {
          *str++ = *fmt;
          if (typechar(&n)) break;
        }
        else fmt--;
        break;
    }
  }
  *str = '\0';
  return str - out;
}

#endif
