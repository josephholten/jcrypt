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

#define F(X,Y,Z) (X & Y) | (~X & Z)
#define G(X,Y,Z) (x & y) | (x & z) | (y & z)
#define H(X,Y,Z) (x ^ y) ^ z

#define FF(a,b,c,d,k,s) a = (a + F(b,c,d) + X[k]) <<< s;
#define GG(a,b,c,d,k,s) a = (a + G(b,c,d) + X[k] + 0x5A82F999) <<< s;
#define HH(a,b,c,d,k,s) a = (a + H(b,c,d) + X[k] + 0x6ED9EBA1) <<< s;

void MD4(char* msg, u64 len, u8* md) {
  // pad to divisible by 64, pad at least one byte
  u8  P  = 64 - (len % 64); 
  u64 N  = len + P;
  u8* M  = malloc(N); // padded msg 

  // 3.1 Step 1. Append Padding Bits
  memset(M, 0, N);
  memcpy(M, msg, len);
  M[len] = 1<<(sizeof(u8)-1); // highest order bit set

  // 3.2 Step 2. Append Length
  //   in little-endian
  memcpy(M+N-sizeof(u64), &N, sizeof(u64));

  // 3.3 Step 3. Initialize MD Buffer
  u32 A = 0x67452301;   
  u32 B = 0xefcdab89;
  u32 C = 0x98badcfe;
  u32 D = 0x10325476;

  // 3.4 Step 4. Process Message in 16-Word Blocks
  for (u64 i = 0; i < N/16; i++) {
    u8 X[16];
    memcpy(X,M,16);

    u32 AA = A, BB = B, CC = C, DD = D;

  }
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
