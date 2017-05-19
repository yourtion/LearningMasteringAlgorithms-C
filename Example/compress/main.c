//
//  main.c
//  MasteringAlgorithms
//  Illustrates data compression (see Chapter 14).
//
//  Created by YourtionGuo on 18/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <ctype.h>
#include <stdio.h>

#include "compress.h"

/// 设置压缩数据的最大大小
#define     DATSIZ      500000

int main(int argc, char **argv)
{
  FILE            *fp;
  unsigned char   original[DATSIZ], *compressed, *restored;
  int             csize, osize, rsize, c, i;

  /// 获取用于压缩的数据
  if ((fp = fopen("sample.txt", "r")) == NULL) return 1;

  i = 0;

  while ((c = getc(fp)) != EOF && i < DATSIZ) {

    original[i] = c;
    i++;

  }

  osize = i;
  fclose(fp);

  /// 使用霍夫曼编码压缩数据

  fprintf(stdout, "Compressing with Huffman coding\n");
  fprintf(stdout, "Compressing...");

  if ((csize = huffman_compress(original, &compressed, osize)) < 0) {

    fprintf(stdout, "\n");
    return 1;
  }

  fprintf(stdout, "Done\n");
  fprintf(stdout, "Uncompressing...");

  if ((rsize = huffman_uncompress(compressed, &restored)) < 0) {

    fprintf(stdout, "\n");
    free(compressed);
    return 1;
  }

  fprintf(stdout, "Done\n");
  fprintf(stdout, "-> osize=%d, csize=%d, rsize=%d\n", osize, csize, rsize);

  if (rsize != osize) {

    fprintf(stdout, "Data was not properly restored\n");
    free(compressed);
    free(restored);
    return 1;

  } else {

    for (i = 0; i < rsize; i++) {

      if (original[i] != restored[i]) {

        fprintf(stdout, "Data was not properly restored\n");

        if (isgraph(original[i])) {
          fprintf(stdout, "-> original[%d]=\"%c\"\n", i, original[i]);
        } else {
          fprintf(stdout, "-> original[%d]=0x%02x\n", i, original[i]);
        }

        if (isgraph(restored[i])) {
          fprintf(stdout, "-> restored[%d]=\"%c\"\n", i, restored[i]);
        }  else {
          fprintf(stdout, "-> restored[%d]=0x%02x\n", i, restored[i]);
        }

        free(compressed);
        free(restored);
        return 1;
      }
    }
  }

  fprintf(stdout, "Data was restored OK\n\n");

  free(compressed);
  free(restored);

  /// 使用 LZ77 压缩数据

  fprintf(stdout, "Compressing with LZ77\n");
  fprintf(stdout, "Compressing...");

  if ((csize = lz77_compress(original, &compressed, osize)) < 0) return 1;

  fprintf(stdout, "Done\n");
  fprintf(stdout, "Uncompressing...");

  if ((rsize = lz77_uncompress(compressed, &restored)) < 0) {

    fprintf(stdout, "\n");
    free(compressed);
    return 1;
  }

  fprintf(stdout, "Done\n");
  fprintf(stdout, "-> osize=%d, csize=%d, rsize=%d\n", osize, csize, rsize);

  if (rsize != osize) {

    fprintf(stdout, "Data was not properly restored\n");
    free(compressed);
    free(restored);
    return 1;

  } else {

    for (i = 0; i < rsize; i++) {

      if (original[i] != restored[i]) {

        fprintf(stdout, "Data was not properly restored\n");

        if (isgraph(original[i])) {
          fprintf(stdout, "-> original[%d]=\"%c\"\n", i, original[i]);
        } else {
          fprintf(stdout, "-> original[%d]=0x%02x\n", i, original[i]);
        }

        if (isgraph(restored[i])) {
          fprintf(stdout, "-> restored[%d]=\"%c\"\n", i, restored[i]);
        } else {
          fprintf(stdout, "-> restored[%d]=0x%02x\n", i, restored[i]);
        }

        free(compressed);
        free(restored);
        return 1;
        
      }
    }
  }
  
  fprintf(stdout, "Data was restored OK\n\n");
  
  free(compressed);
  free(restored);

  return 0;
}
