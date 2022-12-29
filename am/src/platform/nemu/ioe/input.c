#include <am.h>
#include <nemu.h>
#include <amdev.h>
#include <stdbool.h>
#define KEYDOWN_MASK 0x8000
#define KEY_LEN 256

void __am_input_keybrd(AM_INPUT_KEYBRD_T *kbd) {
  uint32_t msg = inl(KBD_ADDR);
  int keycode = msg % KEY_LEN;
  int keydown = msg & KEYDOWN_MASK;
  if(keycode == AM_KEY_NONE) {
    kbd->keydown = false;
    kbd->keycode = AM_KEY_NONE;
  }
  else {
    if(keydown != 0)
      kbd->keydown = true;
    else
      kbd->keydown = false;
    kbd->keycode = keycode;
  }
}
