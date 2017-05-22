//
//  main.c
//  MasteringAlgorithms
//  Illustrates using DES in CBC mode (see Chapter 15).
//
//  Created by YourtionGuo on 22/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "cbc.h"

/// 定义加密字符长度
#define     TXTSIZ      1000

int main(int argc, char **argv)
{
  unsigned char   destmp[TXTSIZ], desptx[TXTSIZ], desctx[TXTSIZ], deskey[8];
  int             i, error = 0;

  /// 使用 CBC 模式执行 DES 加解密

  fprintf(stdout, "Enciphering with DES in CBC mode\n");

  deskey[0] = 0x01;
  deskey[1] = 0xf1;
  deskey[2] = 0x23;
  deskey[3] = 0x4a;
  deskey[4] = 0x1f;
  deskey[5] = 0x22;
  deskey[6] = 0x00;
  deskey[7] = 0xee;

  for (i = 0; i < TXTSIZ; i++) {
    destmp[i] = (i * 23) % 256;
  }

  cbc_encipher(destmp, desctx, deskey, TXTSIZ);
  cbc_decipher(desctx, desptx, deskey, TXTSIZ);

  fprintf(stdout, "deskey: %02x %02x %02x %02x %02x %02x %02x %02x\n",
          deskey[0], deskey[1], deskey[2], deskey[3], deskey[4], deskey[5], deskey[6], deskey[7]);

  for (i = 0; i < TXTSIZ; i++) {

    if (destmp[i] == desptx[i]) {
      fprintf(stdout, "-> destmp[%03d]=%02x, desctx[%03d]=%02x, desptx[%03d]=%02x (OK)\n",
              i, destmp[i], i, desctx[i], i, desptx[i]);
    } else {
      error++;
      fprintf(stdout, "-> destmp[%03d]=%02x, desctx[%03d]=%02x, desptx[%03d]=%02x (ERROR)\n",
              i, destmp[i], i, desctx[i], i, desptx[i]);
    }
  }

  if (error == 0) {
    fprintf(stdout, "Enciphering OK\n");
  } else {
    fprintf(stdout, "Enciphering Error: %d\n", error);
  }

  return 0;
}
