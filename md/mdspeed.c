#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "jstdint.h"
#include "md2.h"
#include "md4.h"

#define KiB 1024
#define MiB KiB*KiB
#define GiB MiB*KiB

clock_t timer() {
  static clock_t t;
  clock_t now = clock();
  clock_t dur = now - t;
  t = now;
  return dur;
}

int main() {
  u64 N = 10*MiB;
  u64 n = 128;

  u8 md[16];
  clock_t tMD2, tMD4, tMD4v2, tMD4v3;
  printf("CLOCKS_PER_SEC = %ld\n", CLOCKS_PER_SEC);

  srandom(0);

  u8* data = malloc(N);
  u64* ldata = (u64*)data;

  for (u64 i = 0; i < N/8; i++)
    ldata[i] = random();

  printf("long strings\n");

  timer();
  MD2(data, N, md);
  tMD2 = timer();
  MD4(data, N, md);
  tMD4 = timer();
  MD4v2(data, N, md);
  tMD4v2 = timer();
  MD4v3(data, N, md);
  tMD4v3 = timer();

  printf("MD2   = %.5e B/s\n", N / (double)tMD2 * CLOCKS_PER_SEC);
  printf("MD4   = %.5e B/s\n", N / (double)tMD4 * CLOCKS_PER_SEC);
  printf("MD4v2 = %.5e B/s\n", N / (double)tMD4v2 * CLOCKS_PER_SEC);
  printf("MD4v3 = %.5e B/s\n", N / (double)tMD4v3 * CLOCKS_PER_SEC);

  printf("short strings\n");
  
  for (u64 i = 0; i + n < N; i += n)
    MD2(data, n, md);
  tMD2 = timer();

  for (u64 i = 0; i + n < N; i += n)
    MD4(data, n, md);
  tMD4 = timer();

  for (u64 i = 0; i + n < N; i += n)
    MD4v2(data, n, md);
  tMD4v2 = timer();

  for (u64 i = 0; i + n < N; i += n)
    MD4v3(data, n, md);
  tMD4v3 = timer();


  printf("MD2   = %.5e B/s\n", N / (double)tMD2 * CLOCKS_PER_SEC);
  printf("MD4   = %.5e B/s\n", N / (double)tMD4 * CLOCKS_PER_SEC);
  printf("MD4v2 = %.5e B/s\n", N / (double)tMD4v2 * CLOCKS_PER_SEC);
  printf("MD4v3 = %.5e B/s\n", N / (double)tMD4v3 * CLOCKS_PER_SEC);




  free(data);
}
