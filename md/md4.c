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

#define ROTL(x, n) (((x) << (n)) | ((x) >> (32-(n))))

#define F(X,Y,Z) (X & Y) | ((~X) & Z)
#define G(X,Y,Z) (X & Y) | (X & Z) | (Y & Z)
#define H(X,Y,Z) (X ^ Y) ^ Z

#define FF(a,b,c,d,xk,s) { a += F(b,c,d) + xk; a = ROTL(a, s); }
#define GG(a,b,c,d,xk,s) { a += G(b,c,d) + xk + 0x5A827999; a = ROTL(a,s); }
#define HH(a,b,c,d,xk,s) { a += H(b,c,d) + xk + 0x6ED9EBA1; a = ROTL(a,s); }

#define S11 3
#define S12 7
#define S13 11
#define S14 19
#define S21 3
#define S22 5
#define S23 9
#define S24 13
#define S31 3
#define S32 9
#define S33 11
#define S34 15

void MD4(char* msg, u64 len, u8* md) {
  // pad to divisible by 64, pad at least one byte
  u8  P  = 64 - (len % 64); 
  u64 N  = len + P;
  u8* M  = malloc(N); // padded msg 

  // 3.1 Step 1. Append Padding Bits
  memset(M, 0, N);
  memcpy(M, msg, len);
  M[len] = 1<<7; // highest order bit set

  // 3.2 Step 2. Append Length
  //   in little-endian
  u64 B = len*8;
  memcpy(M+N-sizeof(u64), &B, sizeof(u64));

  // 3.3 Step 3. Initialize MD Buffer
  u32 a = 0x67452301;   
  u32 b = 0xefcdab89;
  u32 c = 0x98badcfe;
  u32 d = 0x10325476;

  // 3.4 Step 4. Process Message in 16-Word Blocks
  u8 x[16];
  for (u64 i = 0; i < N/16; i++) {
    for (u64 j = 0; j < 16; j++)
      x[j] = M[i*16+j];

    u32 aa = a, bb = b, cc = c, dd = d;

    /* Round 1 */
    FF (a, b, c, d, x[ 0], S11); /* 1 */
    FF (d, a, b, c, x[ 1], S12); /* 2 */
    FF (c, d, a, b, x[ 2], S13); /* 3 */
    FF (b, c, d, a, x[ 3], S14); /* 4 */
    FF (a, b, c, d, x[ 4], S11); /* 5 */
    FF (d, a, b, c, x[ 5], S12); /* 6 */
    FF (c, d, a, b, x[ 6], S13); /* 7 */
    FF (b, c, d, a, x[ 7], S14); /* 8 */
    FF (a, b, c, d, x[ 8], S11); /* 9 */
    FF (d, a, b, c, x[ 9], S12); /* 10 */
    FF (c, d, a, b, x[10], S13); /* 11 */
    FF (b, c, d, a, x[11], S14); /* 12 */
    FF (a, b, c, d, x[12], S11); /* 13 */
    FF (d, a, b, c, x[13], S12); /* 14 */
    FF (c, d, a, b, x[14], S13); /* 15 */
    FF (b, c, d, a, x[15], S14); /* 16 */

    /* Round 2 */
    GG (a, b, c, d, x[ 0], S21); /* 17 */
    GG (d, a, b, c, x[ 4], S22); /* 18 */
    GG (c, d, a, b, x[ 8], S23); /* 19 */
    GG (b, c, d, a, x[12], S24); /* 20 */
    GG (a, b, c, d, x[ 1], S21); /* 21 */
    GG (d, a, b, c, x[ 5], S22); /* 22 */
    GG (c, d, a, b, x[ 9], S23); /* 23 */
    GG (b, c, d, a, x[13], S24); /* 24 */
    GG (a, b, c, d, x[ 2], S21); /* 25 */
    GG (d, a, b, c, x[ 6], S22); /* 26 */
    GG (c, d, a, b, x[10], S23); /* 27 */
    GG (b, c, d, a, x[14], S24); /* 28 */
    GG (a, b, c, d, x[ 3], S21); /* 29 */
    GG (d, a, b, c, x[ 7], S22); /* 30 */
    GG (c, d, a, b, x[11], S23); /* 31 */
    GG (b, c, d, a, x[15], S24); /* 32 */

    /* Round 3 */
    HH (a, b, c, d, x[ 0], S31); /* 33 */
    HH (d, a, b, c, x[ 8], S32); /* 34 */
    HH (c, d, a, b, x[ 4], S33); /* 35 */
    HH (b, c, d, a, x[12], S34); /* 36 */
    HH (a, b, c, d, x[ 2], S31); /* 37 */
    HH (d, a, b, c, x[10], S32); /* 38 */
    HH (c, d, a, b, x[ 6], S33); /* 39 */
    HH (b, c, d, a, x[14], S34); /* 40 */
    HH (a, b, c, d, x[ 1], S31); /* 41 */
    HH (d, a, b, c, x[ 9], S32); /* 42 */
    HH (c, d, a, b, x[ 5], S33); /* 43 */
    HH (b, c, d, a, x[13], S34); /* 44 */
    HH (a, b, c, d, x[ 3], S31); /* 45 */
    HH (d, a, b, c, x[11], S32); /* 46 */
    HH (c, d, a, b, x[ 7], S33); /* 47 */
    HH (b, c, d, a, x[15], S34); /* 48 */

    a += aa; b += bb; c += cc; d += dd;
  }

  // 3.5 Step 5. Output
  memcpy(md,    &a, 4);
  memcpy(md+4,  &b, 4);
  memcpy(md+8,  &c, 4);
  memcpy(md+12, &d, 4);

  memset(x,0,16);
  free(M);
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
