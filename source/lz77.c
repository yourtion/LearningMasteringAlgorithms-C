//
//  lz77.c
//  Algorithms - LZ77（Lempel-Ziv-1977）compress
//
//  Created by YourtionGuo on 19/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "bit.h"
#include "compress.h"

#pragma mark - Private

/**
 确定在前向缓冲区与滑动窗口中匹配的最长短语

 @param window 滑动窗口
 @param buffer 前向缓冲区
 @param offset 滑动窗口中匹配串的位置
 @param next 前向缓冲区中匹配串后一位的符号
 @return 匹配的最长短语长度
 */
static int compare_win(const unsigned char *window,
                       const unsigned char *buffer,
                       int *offset, unsigned char *next)
{

  int       match, longest, i, j, k;

  /// 初始化 offset，尽管只会在找到结果时赋值
  *offset = 0;

  /// 如果没找到匹配，则返回 0 并将 next 指向前向缓冲区
  longest = 0;
  *next = buffer[0];

  /// 在滑动窗口中找到前向缓冲区的最佳匹配

  for (k = 0; k < LZ77_WINDOW_SIZE; k++) {

    i = k;
    j = 0;
    match = 0;

    /// 确定有滑动窗口偏移 k 中有多少符号匹配

    while (i < LZ77_WINDOW_SIZE && j < LZ77_BUFFER_SIZE - 1) {

      if (window[i] != buffer[j]) break;

      match++;
      i++;
      j++;

    }

    /// 保存偏移量，长度以及最后符号位置
    if (match > longest) {

      *offset = k;
      longest = match;
      *next = buffer[j];

    }
  }

  return longest;
}

#pragma mark - Public


int lz77_compress(const unsigned char *original, unsigned char **compressed, int size)
{
  unsigned long   token;
  unsigned char   window[LZ77_WINDOW_SIZE], buffer[LZ77_BUFFER_SIZE], *comp, *temp, next;
  int             offset, length, remaining, tbits, hsize, ipos, opos, tpos, i;

  /// 初始化最初的压缩结果为空
  *compressed = NULL;

  /// 写入头部数据
  hsize = sizeof(int);

  if ((comp = (unsigned char *)malloc(hsize)) == NULL) return -1;

  memcpy(comp, &size, sizeof(int));

  /// 初始化滑动窗口和前向缓冲区

  memset(window, 0, LZ77_WINDOW_SIZE);
  memset(buffer, 0, LZ77_BUFFER_SIZE);

  /// 加载前向缓冲区内容
  ipos = 0;

  for (i = 0; i < LZ77_BUFFER_SIZE && ipos < size; i++) {

    buffer[i] = original[ipos];
    ipos++;
  }

  /// 压缩数据

  opos = hsize * 8;
  remaining = size;

  while (remaining > 0) {

    if ((length = compare_win(window, buffer, &offset, &next)) != 0) {

      /// 编码短语标记
      token = 0x00000001 << (LZ77_PHRASE_BITS - 1);

      /// 设置偏移量当在滑动窗口中找到结果
      token = token | (offset << (LZ77_PHRASE_BITS - LZ77_TYPE_BITS -
                                  LZ77_WINOFF_BITS));

      /// 设置最大匹配长度
      token = token | (length << (LZ77_PHRASE_BITS - LZ77_TYPE_BITS -
                                  LZ77_WINOFF_BITS - LZ77_BUFLEN_BITS));

      /// 设置前向缓冲区中匹配后的下一个符号
      token = token | next;

      /// 设置短语标记中的位长度
      tbits = LZ77_PHRASE_BITS;
    } else {

      /// 编码短语标记
      token = 0x00000000;

      /// 设置未找到的符号
      token = token | next;

      /// 设置短语标记中的位长度
      tbits = LZ77_SYMBOL_BITS;
    }

    /// 确保短语标记是以大端字节格式存放
    token = htonl(token);

    /// 将短语标记写入压缩后数据缓冲区
    for (i = 0; i < tbits; i++) {

      if (opos % 8 == 0) {

        /// 初始化另外的字节以存放新短语标记
        if ((temp = (unsigned char *)realloc(comp,(opos / 8) + 1)) == NULL) {

          free(comp);
          return -1;
        }

        comp = temp;
      }

      tpos = (sizeof(unsigned long) * 8) - tbits + i;
      bit_set(comp, opos,  bit_get((unsigned char *)&token, tpos));
      opos++;
    }

    /// 调整短语长度以描述未匹配符号
    length++;

    /// 将前向缓冲区中的数据拷贝到滑动窗口
    memmove(&window[0], &window[length], LZ77_WINDOW_SIZE - length);
    memmove(&window[LZ77_WINDOW_SIZE - length], &buffer[0], length);

    /// 加载更多数据到前向缓冲区
    memmove(&buffer[0], &buffer[length], LZ77_BUFFER_SIZE - length);

    for (i = LZ77_BUFFER_SIZE - length; i<LZ77_BUFFER_SIZE && ipos<size; i++) {

      buffer[i] = original[ipos];
      ipos++;
    }

    /// 调整剩余符号的数量
    remaining = remaining - length;
  }

  /// 将缓冲区指向已压缩数据
  *compressed = comp;

  /// 返回压缩后数据的长度
  return ((opos - 1) / 8) + 1;
}


int lz77_uncompress(const unsigned char *compressed, unsigned char **original) {

  unsigned char   window[LZ77_WINDOW_SIZE], buffer[LZ77_BUFFER_SIZE], *orig, *temp, next;
  int             offset, length, remaining, hsize, size, ipos, opos, tpos, state, i;

  /// 初始化最初的解压结果为空
  *original = orig = NULL;

  /// 获取压缩数据中的头部信息
  hsize = sizeof(int);
  memcpy(&size, compressed, sizeof(int));

  /// 初始化滑动窗口和前向缓冲区
  memset(window, 0, LZ77_WINDOW_SIZE);
  memset(buffer, 0, LZ77_BUFFER_SIZE);

  /// 解压数据

  ipos = hsize * 8;
  opos = 0;
  remaining = size;

  while (remaining > 0) {

    /// 获取压缩数据的下一位
    state = bit_get(compressed, ipos);
    ipos++;

    if (state == 1) {

      /// 处理短语标记
      memset(&offset, 0, sizeof(int));

      for (i = 0; i < LZ77_WINOFF_BITS; i++) {

        tpos = (sizeof(int) * 8) - LZ77_WINOFF_BITS + i;
        bit_set((unsigned char *)&offset, tpos, bit_get(compressed, ipos));
        ipos++;
      }

      memset(&length, 0, sizeof(int));

      for (i = 0; i < LZ77_BUFLEN_BITS; i++) {

        tpos = (sizeof(int) * 8) - LZ77_BUFLEN_BITS + i;
        bit_set((unsigned char *)&length, tpos, bit_get(compressed, ipos));
        ipos++;
      }

      next = 0x00;

      for (i = 0; i < LZ77_NEXT_BITS; i++) {

        tpos = (sizeof(unsigned char) * 8) - LZ77_NEXT_BITS + i;
        bit_set((unsigned char *)&next, tpos, bit_get(compressed, ipos));
        ipos++;
      }

      /// 确保当前编码是以大端字节格式读取
      offset = ntohl(offset);
      length = ntohl(length);

      /// 将滑动窗口中的短语写入原始数据缓冲区

      i = 0;

      if (opos > 0) {

        if ((temp = (unsigned char *)realloc(orig, opos+length+1)) == NULL) {

          free(orig);
          return -1;
        }

        orig = temp;

      } else {

        if ((orig = (unsigned char *)malloc(length + 1)) == NULL) return -1;
      }

      while (i < length && remaining > 0) {

        orig[opos] = window[offset + i];
        opos++;

        /// 记录前向缓冲区中的符号直到更新入滑动窗口
        buffer[i] = window[offset + i];
        i++;

        /// 更新生于的需要处理的符号数量
        remaining--;
      }

      /// 将未匹配的符号写入元素数据缓冲区
      if (remaining > 0) {

        orig[opos] = next;
        opos++;

        /// 同时记录当前符号到前向缓冲区中
        buffer[i] = next;

        /// 调整剩余需要处理的未匹配符号
        remaining--;
      }

      /// 调整未匹配符号的短语长度
      length++;

    } else {

      /// 处理已匹配的短语标记

      next = 0x00;

      for (i = 0; i < LZ77_NEXT_BITS; i++) {

        tpos = (sizeof(unsigned char) * 8) - LZ77_NEXT_BITS + i;
        bit_set((unsigned char *)&next, tpos, bit_get(compressed, ipos));
        ipos++;

      }

      /// 将符号写入前向缓冲区

      if (opos > 0) {

        if ((temp = (unsigned char *)realloc(orig, opos + 1)) == NULL) {

          free(orig);
          return -1;
        }

        orig = temp;

      } else {

        if ((orig = (unsigned char *)malloc(1)) == NULL) return -1;
      }

      orig[opos] = next;
      opos++;

      /// 记录前向缓冲区中的符号直到更新入滑动窗口
      if (remaining > 0) {
        buffer[0] = next;
      }

      /// 调整剩余需要处理的未匹配符号
      remaining--;

      /// 调整未匹配符号的短语长度
      length = 1;
    }

    /// 将前向缓冲区中的数据拷贝到滑动窗口
    memmove(&window[0], &window[length], LZ77_WINDOW_SIZE - length);
    memmove(&window[LZ77_WINDOW_SIZE - length], &buffer[0], length);
  }

  /// 将缓冲区指向已压缩数据
  *original = orig;

  /// 返回原始数据的长度
  return opos;
}
