#include <stdio.h>
#include <string.h>

#include "md4.h"
#include "jprint.h"

int main() {
  char* tests[] = {
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
    MD4v3((u8*)tests[i], len, md);
    printf("msg (%ld)=\n  %s\n", len, tests[i]);
    print_hexstring("md=", md, 16);
  }
}
