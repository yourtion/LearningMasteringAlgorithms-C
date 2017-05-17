//
//  main.c
//  MasteringAlgorithms
//  Illustrates using bit operations (see Chapter 14).
//
//  Created by YourtionGuo on 17/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <stdio.h>
#include <string.h>

#include "bit.h"

int main(int argc, char **argv)
{
  unsigned char   bits1[8], bits2[8], bits3[8];
  int             i;

  /// 使用 64-bit 的位执行位操作

  for (i = 0; i < 8; i++) {

    bits1[i] = 0x00;
    bits2[i] = 0x00;
    bits3[i] = 0x00;

  }

  fprintf(stdout, "Initially\n");

  fprintf(stdout, "-> bits1: %02x %02x %02x %02x %02x %02x %02x %02x\n",
          bits1[0], bits1[1], bits1[2], bits1[3], bits1[4], bits1[5], bits1[6], bits1[7]);

  fprintf(stdout, "-> bits2: %02x %02x %02x %02x %02x %02x %02x %02x\n",
          bits2[0], bits2[1], bits2[2], bits2[3], bits2[4], bits2[5], bits2[6], bits2[7]);

  bit_set(bits1, 15, 1);
  bit_set(bits1, 16, 1);
  bit_set(bits1, 32, 1);
  bit_set(bits1, 63, 1);
  bit_set(bits2,  0, 1);
  bit_set(bits2, 15, 1);

  fprintf(stdout, "After setting bits 15, 16, 32, 63 of bits1 and bits 00, 15 of bits2\n");

  fprintf(stdout, "-> bits1: %02x %02x %02x %02x %02x %02x %02x %02x\n",
          bits1[0], bits1[1], bits1[2], bits1[3], bits1[4], bits1[5], bits1[6], bits1[7]);

  fprintf(stdout, "-> bits2: %02x %02x %02x %02x %02x %02x %02x %02x\n",
          bits2[0], bits2[1], bits2[2], bits2[3], bits2[4], bits2[5], bits2[6], bits2[7]);

  fprintf(stdout, "Bit 63 of bits1 is %d\n", bit_get(bits1, 63));
  fprintf(stdout, "Bit 62 of bits1 is %d\n", bit_get(bits1, 62));
  fprintf(stdout, "Bit 00 of bits2 is %d\n", bit_get(bits2,  0));
  fprintf(stdout, "Bit 01 of bits2 is %d\n", bit_get(bits2,  1));

  bit_xor(bits1, bits2, bits3, 32);

  fprintf(stdout, "bits3 is bits1 XOR bits2 (32 bits)\n");

  fprintf(stdout, "-> bits3: %02x %02x %02x %02x %02x %02x %02x %02x\n",
          bits3[0], bits3[1], bits3[2], bits3[3], bits3[4], bits3[5], bits3[6], bits3[7]);

  bit_xor(bits1, bits2, bits3, 64);

  fprintf(stdout, "bits3 is bits1 XOR bits2 (64 bits)\n");

  fprintf(stdout, "-> bits3: %02x %02x %02x %02x %02x %02x %02x %02x\n",
          bits3[0], bits3[1], bits3[2], bits3[3], bits3[4], bits3[5], bits3[6], bits3[7]);

  bit_rot_left(bits1, 64, 1);

  fprintf(stdout, "After rotating bits1 left x 1 (64 bits)\n");

  fprintf(stdout, "-> bits1: %02x %02x %02x %02x %02x %02x %02x %02x\n",
          bits1[0], bits1[1], bits1[2], bits1[3], bits1[4], bits1[5], bits1[6], bits1[7]);

  bit_rot_left(bits2, 64, 1);

  fprintf(stdout, "After rotating bits2 left x 1 (64 bits)\n");

  fprintf(stdout, "-> bits2: %02x %02x %02x %02x %02x %02x %02x %02x\n",
          bits2[0], bits2[1], bits2[2], bits2[3], bits2[4], bits2[5], bits2[6], bits2[7]);

  bit_rot_left(bits2, 16, 7);

  fprintf(stdout, "After rotating bits2 left x 7 (16 bits)\n");

  fprintf(stdout, "-> bits2: %02x %02x %02x %02x %02x %02x %02x %02x\n",
          bits2[0], bits2[1], bits2[2], bits2[3], bits2[4], bits2[5], bits2[6], bits2[7]);

  bit_rot_left(bits2, 8, 2);

  fprintf(stdout, "After rotating bits2 left x 2 (8 bits)\n");

  fprintf(stdout, "-> bits2: %02x %02x %02x %02x %02x %02x %02x %02x\n",
          bits2[0], bits2[1], bits2[2], bits2[3], bits2[4], bits2[5], bits2[6], bits2[7]);

  for (i = 0; i < 8; i++) {

    bits2[i] = 0x00;

  }

  bit_set(bits2,  0, 1);
  bit_set(bits2,  3, 1);
  bit_set(bits2,  8, 1);
  bit_set(bits2, 27, 1);

  fprintf(stdout, "After clearing and setting bits 0, 3, 8, 27 of bits2\n");

  fprintf(stdout, "-> bits2: %02x %02x %02x %02x %02x %02x %02x %02x\n",
          bits2[0], bits2[1], bits2[2], bits2[3], bits2[4], bits2[5], bits2[6], bits2[7]);

  bit_rot_left(bits2, 11, 6);

  fprintf(stdout, "After rotating bits2 left x 6 (11 bits)\n");

  fprintf(stdout, "-> bits2: %02x %02x %02x %02x %02x %02x %02x %02x\n",
          bits2[0], bits2[1], bits2[2], bits2[3], bits2[4], bits2[5], bits2[6], bits2[7]);

  for (i = 0; i < 8; i++) {

    bits2[i] = 0x00;

  }

  bit_set(bits2,  0, 1);
  bit_set(bits2,  3, 1);
  bit_set(bits2,  8, 1);
  bit_set(bits2, 27, 1);

  fprintf(stdout, "After clearing and setting bits 0, 3, 8, 27 of bits2\n");

  fprintf(stdout, "-> bits2: %02x %02x %02x %02x %02x %02x %02x %02x\n",
          bits2[0], bits2[1], bits2[2], bits2[3], bits2[4], bits2[5], bits2[6], bits2[7]);
  
  bit_rot_left(bits2, 28, 4);
  
  fprintf(stdout, "After rotating bits2 left x 4 (28 bits)\n");
  
  fprintf(stdout, "-> bits2: %02x %02x %02x %02x %02x %02x %02x %02x\n",
          bits2[0], bits2[1], bits2[2], bits2[3], bits2[4], bits2[5], bits2[6], bits2[7]);
  
  return 0;
}
