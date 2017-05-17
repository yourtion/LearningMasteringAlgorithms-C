//
//  bit.c
//  Algorithms - Bit operations
//
//  Created by YourtionGuo on 17/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//


#include <string.h>

#include "bit.h"

#pragma mark - Public

int bit_get(const unsigned char *bits, int pos)
{
  unsigned char   mask;
  int             i;

  /// 设置位获取掩码
  mask = 0x80;

  for (i = 0; i < (pos % 8); i++) {
    mask = mask >> 1;
  }

  /// 获取位
  return (((mask & bits[(int)(pos / 8)]) == mask) ? 1 : 0);
}


void bit_set(unsigned char *bits, int pos, int state)
{
  unsigned char   mask;
  int             i;

  /// 设置位获取掩码
  mask = 0x80;

  for (i = 0; i < (pos % 8); i++) {
    mask = mask >> 1;
  }

  /// 设置位
  if (state) {
    bits[pos / 8] = bits[pos / 8] | mask;
  } else {
    bits[pos / 8] = bits[pos / 8] & (~mask);
  }

  return;
}


void bit_xor(const unsigned char *bits1, const unsigned char *bits2, unsigned char *bitsx, int size)
{
  int       i;

  /// 按位计算两个缓存区的异或值

  for (i = 0; i < size; i++) {

    if (bit_get(bits1, i) != bit_get(bits2, i)) {
      bit_set(bitsx, i, 1);
    } else {
      bit_set(bitsx, i, 0);
    }
  }

  return;
}



void bit_rot_left(unsigned char *bits, int size, int count)
{
  int       fbit = 0, lbit, i, j;

  /// 向左轮转缓冲区特定位数

  if (size > 0) {

    for (j = 0; j < count; j++) {

      for (i = 0; i <= ((size - 1) / 8); i++) {

        /// 获取即将被替换的位的值
        lbit = bit_get(&bits[i], 0);

        if (i == 0) {

          /// 将第一个位保存起来
          fbit = lbit;

        } else {

          /// 将前一个字节最右边的位移到当前字节的最左边
          bit_set(&bits[i - 1], 7, lbit);
        }

        /// 将特定位向左移动
        bits[i] = bits[i] << 1;
      }

      /// 将其最右边的位移动到首字节的最高位上
      
      bit_set(bits, size - 1, fbit);
    }
  }
  
  return;
}

