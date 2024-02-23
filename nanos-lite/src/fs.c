#include <fs.h>

typedef size_t (*ReadFn) (void *buf, size_t offset, size_t len);
typedef size_t (*WriteFn) (const void *buf, size_t offset, size_t len);

typedef struct {
  char *name;
  size_t size;
  size_t disk_offset;
  size_t open_offset;
  ReadFn read;
  WriteFn write;
} Finfo;

enum {FD_STDIN, FD_STDOUT, FD_STDERR, FD_EVENT, PROC_DISP, FD_FB};

size_t invalid_read(void *buf, size_t offset, size_t len) {
  panic("should not reach here");
  return 0;
}

size_t invalid_write(const void *buf, size_t offset, size_t len) {
  panic("should not reach here");
  return 0;
}

size_t ramdisk_read(void *buf, size_t offset, size_t len);
size_t ramdisk_write(const void *buf, size_t offset, size_t len);
size_t dispinfo_read(void *buf, size_t offset, size_t len);
size_t serial_write(const void *buf, size_t offset, size_t len);
size_t events_read(void *buf, size_t offset, size_t len);
size_t fb_write(const void *buf, size_t offset, size_t len);
/* This is the information about all files in disk. */
static Finfo file_table[] __attribute__((used)) = {
  [FD_STDIN]  = {"stdin", 0, 0, 0, invalid_read, invalid_write},
  [FD_STDOUT] = {"stdout", 0, 0, 0, invalid_read, serial_write},
  [FD_STDERR] = {"stderr", 0, 0, 0, invalid_read, serial_write},
  [FD_EVENT] = {"/dev/events", 0, 0, 0, events_read, invalid_write},
  [PROC_DISP] = {"/proc/dispinfo", 0, 0, 0, dispinfo_read, invalid_write},
  [FD_FB]     = {"/dev/fb", 0, 0, 0, invalid_read, fb_write},
#include "files.h"
};

void init_fs() {
  // TODO: initialize the size of /dev/fb
  file_table[FD_FB].size = 0x200000; // size from am.
}

int fs_open(const char *pathname, int flags, int mode) {
  int num = sizeof(file_table) / sizeof(Finfo);
  for(int i = 0; i < num; ++i) {
    if(strcmp(pathname, file_table[i].name) == 0) return i;
  }
  panic("Wrong file pathname: %s.", pathname);
}

size_t fs_read(int fd, void *buf, size_t len) {
  if (file_table[fd].read == NULL) {
    if (file_table[fd].open_offset + len > file_table[fd].size) {
      len = file_table[fd].size - file_table[fd].open_offset;
      // Log("Warning: fs_read offset has been reset.");
    }
    size_t ret = ramdisk_read(buf, file_table[fd].disk_offset + file_table[fd].open_offset, len);
    file_table[fd].open_offset += len;
    return ret;
  } 
  else return file_table[fd].read(buf, file_table[fd].open_offset, len);
}

size_t fs_write(int fd, const void *buf, size_t len) {
  if (file_table[fd].write == NULL) {
    if (file_table[fd].open_offset + len > file_table[fd].size) {
      len = file_table[fd].size - file_table[fd].open_offset;
      // Log("Warning: fs_write offset has been reset.");
    }
    size_t ret = ramdisk_write(buf, file_table[fd].disk_offset + file_table[fd].open_offset, len);
    file_table[fd].open_offset += len;
    return ret;
  } 
  else return file_table[fd].write(buf, file_table[fd].open_offset, len);
}

size_t fs_lseek(int fd, size_t offset, int whence) {
  switch (whence) {
    case SEEK_SET:
      file_table[fd].open_offset = offset;
      break;
    case SEEK_CUR:
      file_table[fd].open_offset += offset;
      break;
    case SEEK_END:
      file_table[fd].open_offset = file_table[fd].size + offset;
      break;
    default:
      panic("error with fs_lseek");
  }
  return file_table[fd].open_offset;
}

int fs_close(int fd) {
  file_table[fd].open_offset = 0;
  return 0;
}

// size_t write(int fd, intptr_t buf, size_t count) {
//   if(fd == 1 || fd == 2) {
//     char* buff = (char*)buf;
//     for(int i = 0; i < count; ++i) {
//       putch(buff[i]);
//     }
//     return count;
//   }
//   else {
//     return -1;
//   }
// }
