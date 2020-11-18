#include <stdio.h>
#include <stdlib.h>

void printEntropy(u_int32_t *entropy) {
  for (int i = 0; i < 32; i++) {
    printf("%08x ",entropy[i]);
    if (i % 8 == 7) {
      printf("\n");
    }
  }
  printf("\n");
}

int main(void) {
  u_int32_t entropy[32] = {0};
  u_int32_t seed = 0xDEADBEEF;
  
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 32; j++) {
      seed ^= entropy[j];
      entropy[j] ^= seed;
      seed = (seed >> (entropy[j] & 0x3)) | (seed << ((entropy[j] >> 4) & 0x3));
    }
    entropy[seed & 0xF] = seed;
    seed ^= entropy[(seed >> 4) & 0xF];
    printEntropy(entropy);
    printf("seed: %08x\n",seed);
  }
}
