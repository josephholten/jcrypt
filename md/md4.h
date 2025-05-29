#pragma once

#include <string.h>
#include "jstdint.h"

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

#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (y)) | ((x) & (z)) | ((y) & (z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))

#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

#define FF(a, b, c, d, x, s) { \
    (a) += F ((b), (c), (d)) + (x); \
    (a) = ROTATE_LEFT ((a), (s)); \
  }
#define GG(a, b, c, d, x, s) { \
    (a) += G ((b), (c), (d)) + (x) + (u32)0x5a827999; \
    (a) = ROTATE_LEFT ((a), (s)); \
  }
#define HH(a, b, c, d, x, s) { \
    (a) += H ((b), (c), (d)) + (x) + (u32)0x6ed9eba1; \
    (a) = ROTATE_LEFT ((a), (s)); \
  }


static void MD4Transform (u32* state, u8* block) {
  u32 a = state[0], b = state[1], c = state[2], d = state[3];
  u32* x = (u32*) block;

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

  state[0] += a;
  state[1] += b;
  state[2] += c;
  state[3] += d;
}



void MD4(u8* msg, u64 len, u8* md) {
  // pad to 56 mod 64, padding at least one byte, then add 8
  u64 mlen = len % 64;
  u64 P  = (mlen < 56) ? (56 - mlen) : (56 + 64 - mlen);
  u64 N  = len + P + 8;
  u8* M  = malloc(N); // padded msg 

  // 3.1 Step 1. Append Padding Bits
  memset(M, 0, N);
  memcpy(M, msg, len);
  M[len] = 1<<7; // highest order bit set

  // 3.2 Step 2. Append Length
  //   in bits in little-endian
  u64* pB = (u64*)(M+len+P);
  *pB = len*8;

  // 3.3 Step 3. Initialize MD Buffer
  u8 init[16] = {
    0x01, 0x23, 0x45, 0x67,
    0x89, 0xab, 0xcd, 0xef,
    0xfe, 0xdc, 0xba, 0x98,
    0x76, 0x54, 0x32, 0x10,
  };
  u32* state = (u32*)init;

  // 3.4 Step 4. Process Message in 16-Word Blocks
  //   Word = u32
  for (u64 i = 0; i < N; i += 64)
    MD4Transform(state,&M[i]);

  // 3.5 Step 5. Output
  memcpy(md, state, 16);
  free(M);
}



void MD4v2(u8* msg, u64 len, u8* md) {
  // 3.3 Step 3. Initialize MD Buffer
  u8 init[16] = {
    0x01, 0x23, 0x45, 0x67,
    0x89, 0xab, 0xcd, 0xef,
    0xfe, 0xdc, 0xba, 0x98,
    0x76, 0x54, 0x32, 0x10,
  };
  u32* state = (u32*)init;

  // 3.4 Step 4. Process Message in 16-Word Blocks
  //   as many 16-Word blocks as are available unpadded
  u64 i = 0;
  for (; i + 64 <= len; i += 64)
    MD4Transform(state, msg+i);

  u8 buf[128] = {0};

  // copy out remaining
  const u64 rem = len - i;
  memcpy(buf, msg+i, rem);

  // pad to 56 mod 64, padding at least one byte, then add 8
  const u64 pad = (rem < 56) ? (56 - rem) : (56+64 - rem);

  // 3.1 Step 1. Append Padding Bits
  buf[rem] = 0x80; // highest bit set

  // 3.2 Step 2. Append Length
  //   b in bits in little-endian
  u64* pb = (u64*)(buf+rem+pad);
  *pb = len*8;

  // transform the padding and length
  MD4Transform(state,buf);
  if (rem+pad+8 == 128)
    MD4Transform(state,buf+64);

  // 3.5 Step 5. Output
  memcpy(md, state, 16);
}


