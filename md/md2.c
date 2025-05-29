#include <string.h>
#include <stdlib.h>
#include "md2.h"

static u8 S[256] = {
  41, 46, 67, 201, 162, 216, 124, 1, 61, 54, 84, 161, 236, 240, 6,
  19, 98, 167, 5, 243, 192, 199, 115, 140, 152, 147, 43, 217, 188,
  76, 130, 202, 30, 155, 87, 60, 253, 212, 224, 22, 103, 66, 111, 24,
  138, 23, 229, 18, 190, 78, 196, 214, 218, 158, 222, 73, 160, 251,
  245, 142, 187, 47, 238, 122, 169, 104, 121, 145, 21, 178, 7, 63,
  148, 194, 16, 137, 11, 34, 95, 33, 128, 127, 93, 154, 90, 144, 50,
  39, 53, 62, 204, 231, 191, 247, 151, 3, 255, 25, 48, 179, 72, 165,
  181, 209, 215, 94, 146, 42, 172, 86, 170, 198, 79, 184, 56, 210,
  150, 164, 125, 182, 118, 252, 107, 226, 156, 116, 4, 241, 69, 157,
  112, 89, 100, 113, 135, 32, 134, 91, 207, 101, 230, 45, 168, 2, 27,
  96, 37, 173, 174, 176, 185, 246, 28, 70, 97, 105, 52, 64, 126, 15,
  85, 71, 163, 35, 221, 81, 175, 58, 195, 92, 249, 206, 186, 197,
  234, 38, 44, 83, 13, 110, 133, 40, 132, 9, 211, 223, 205, 244, 65,
  129, 77, 82, 106, 220, 55, 200, 108, 193, 171, 250, 36, 225, 123,
  8, 12, 189, 177, 74, 120, 136, 149, 139, 227, 99, 232, 109, 233,
  203, 213, 254, 59, 0, 29, 57, 242, 239, 183, 14, 102, 88, 208, 228,
  166, 119, 114, 248, 235, 117, 75, 10, 49, 68, 80, 180, 143, 237,
  31, 26, 219, 153, 141, 51, 159, 17, 131, 20
};

void MD2(u8* msg, u64 len, u8* md) {
  u8  P  = 16 - (len % 16); // padding length
  u64 N  = len + P;         // padded msg length
  u64 Np = N + 16;          // padded msg length + checksum
  u8* M  = malloc(Np);      // msg with padding and checksum
  u8* C  = M + N;           // checksum

  memcpy(M, msg, len);
  memset(M+len, P, P);

  // NOTE: from RFC1423, sect 2.1:
  //  An error has been identified in RFC 1319.  The
  //  statement in the text of Section 3.2 which reads "Set C[j] to S[c xor L]"
  //  should read "Set C[j] to S[c xor L] xor C[j]".  Note that the C
  //  source code in the appendix of RFC 1319 is correct.

  // 3.2 Step 2. Append Checksum
  memset(C, 0, 16);
  u8 L = 0;
  for (u64 i = 0; i < N/16; i++) {
    for (u64 j = 0; j < 16; j++) {
      u8 c = M[i*16+j];
      C[j] ^= S[c ^ L];
      L = C[j];
    }
  }

  // 3.3 Step 3. Initialize MD Buffer
  u8 X[48] = {0};

  // 3.4 Step 4. Process Message in 16-Byte Blocks
  for (u64 i = 0; i < Np/16; i++) {
    for (u64 j = 0; j < 16; j++) {
      X[16+j] = M[i*16+j];
      X[32+j] = M[i*16+j] ^ X[j];
    }

    u8 t = 0;
    for (u64 j = 0; j < 18; j++) {
      for (u64 k = 0; k < 48; k++)
        t = X[k] = X[k] ^ S[t];
      t += j; // modulo 256 = sizeof(u8)
    }
  }

  // 3.5 Step 5. Output
  memcpy(md,X,16);

  free(M);
}

