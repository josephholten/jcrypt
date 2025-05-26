#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define u8   uint8_t
#define u16  uint16_t
#define u32  uint32_t
#define u64  uint64_t
#define u128 __int128

void print_hexchar(u8 nibble) {
  nibble &= 0x0F;
  if (nibble < 10) {
    putchar('0' + nibble);
  } else {
    putchar('a' + nibble - 10);
  }
}

void print_hexstring(char* msg, u8* hs, u64 len) {
  if (msg)
    printf("%s\n  ", msg);
  for (u64 i = 0; i < len; i++) {
    print_hexchar(hs[i] >> 4); // high
    print_hexchar(hs[i] & 0x0F); // low
  }
  putchar('\n');
}

void MD4(char* msg, u64 len, u8* md) {
}


int main() {
  u8* tests[] = {
    "",
    "a",
    "abc",
    "message digest",
    "abcdefghijklmnopqrstuvwxyz",
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789",
    "12345678901234567890123456789012345678901234567890123456789012345678901234567890",
  };
  u64 num_tests = sizeof(tests)/sizeof(u8*);
  u8 md[16];
  for (u64 i = 0; i < num_tests; i++) {
    u64 len = strlen(tests[i]);
    MD4(tests[i], len, md);
    printf("msg (%d)=\n  %s\n", len, tests[i]);
    print_hexstring("md=", md, 16);
  }
}
