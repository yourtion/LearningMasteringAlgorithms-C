//
//  des.c
//  Algorithms - DES（ Data Encryption Standard ）
//
//  Created by YourtionGuo on 22/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "bit.h"
#include "encrypt.h"

#pragma mark - Private

/// DES 中密钥的转换表
static const int DesTransform[56] =
{
  57, 49, 41, 33, 25, 17,  9,  1, 58, 50, 42, 34, 26, 18,
  10,  2, 59, 51, 43, 35, 27, 19, 11,  3, 60, 52, 44, 36,
  63, 55, 47, 39, 31, 23, 15,  7, 62, 54, 46, 38, 30, 22,
  14,  6, 61, 53, 45, 37, 29, 21, 13,  5, 28, 20, 12,  4
};

/// 针对 DES 子密钥每一轮的旋转次数
static const int DesRotations[16] =
{
  1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};

/// DES 子密钥的置换选择
static const int DesPermuted[48] =
{
  14, 17, 11, 24,  1,  5,  3, 28, 15,  6, 21, 10,
  23, 19, 12,  4, 26,  8, 16,  7, 27, 20, 13,  2,
  41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
  44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
};

/// DES 中数据块的初始置换
static const int DesInitial[64] =
{
  58, 50, 42, 34, 26, 18, 10,  2, 60, 52, 44, 36, 28, 20, 12,  4,
  62, 54, 46, 38, 30, 22, 14,  6, 64, 56, 48, 40, 32, 24, 16,  8,
  57, 49, 41, 33, 25, 17,  9,  1, 59, 51, 43, 35, 27, 19, 11,  3,
  61, 53, 45, 37, 29, 21, 13,  5, 63, 55, 47, 39, 31, 23, 15,  7
};

/// DES 中数据块的扩展置换
static const int DesExpansion[48] =
{
  32,  1,  2,  3,  4,  5,  4,  5,  6,  7,  8,  9,
   8,  9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
  16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
  24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32,  1
};

/// DES 中数据块的S盒替换
static const int DesSbox[8][4][16] =
{
  {
    {14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7},
    { 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8},
    { 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0},
    {15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13},
  },

  {
    {15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10},
    { 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5},
    { 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15},
    {13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9},
  },

  {
    {10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8},
    {13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1},
    {13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7},
    { 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12},
  },

  {
    { 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15},
    {13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9},
    {10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4},
    { 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14},
  },

  {
    { 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9},
    {14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6},
    { 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14},
    {11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3},
  },

  {
    {12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11},
    {10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8},
    { 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6},
    { 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13},
  },

  {
    { 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1},
    {13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6},
    { 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2},
    { 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12},
  },

  {
    {13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7},
    { 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2},
    { 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8},
    { 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11},
  },
};

/// DES 中数据块的P盒置换
static const int DesPbox[32] =
{
  16,  7, 20, 21, 29, 12, 28, 17,  1, 15, 23, 26,  5, 18, 31, 10,
  2,  8, 24, 14, 32, 27,  3,  9, 19, 13, 30,  6, 22, 11,  4, 25
};

/// DES 中数据块的最终置换
static const int DesFinal[64] =
{
  40,  8, 48, 16, 56, 24, 64, 32, 39,  7, 47, 15, 55, 23, 63, 31,
  38,  6, 46, 14, 54, 22, 62, 30, 37,  5, 45, 13, 53, 21, 61, 29,
  36,  4, 44, 12, 52, 20, 60, 28, 35,  3, 43, 11, 51, 19, 59, 27,
  34,  2, 42, 10, 50, 18, 58, 26, 33,  1, 41,  9, 49, 17, 57, 25
};

/*****************************************************************************
 *                                                                            *
 *  Define a type for whether to encipher or decipher data.                   *
 *                                                                            *
 *****************************************************************************/
/// 定义操作为加密或者解密
typedef enum DesEorD_
{
  encipher, /// 加密
  decipher  /// 解密
} DesEorD;


/**
 根据一个特定的表在一个缓冲区中置换位

 @param bits 缓冲区
 @param mapping 特定的置换表
 @param n 位数
 */
static void permute(unsigned char *bits, const int *mapping, int n)
{
  unsigned char   temp[8];
  int             i;

  /// 对缓冲区中 n 条数据进行置换操作

  memset(temp, 0, (int)ceil(n / 8));

  for (i = 0; i < n; i++) {
    bit_set(temp, i, bit_get(bits, mapping[i] - 1));
  }

  memcpy(bits, temp, (int)ceil(n / 8));

  return;
}


/**
 DES 加解密主函数

 @param source 源缓冲区
 @param target 结果缓冲区
 @param key 指定64位的密钥（NULL 表示重用子密钥）
 @param direction 执行加密或解密操作
 @return 执行成功返回 0
 */
static int des_main(const unsigned char *source, unsigned char *target,
                    const unsigned char *key, DesEorD direction)
{
  static unsigned char subkeys[16][7];
  unsigned char         temp[8], lkey[4], rkey[4], lblk[6], rblk[6], fblk[6], xblk[6], sblk;
  int                   row, col, i, j, k, p;

  /// 如果 key 为 NULL，使用上次计算的子密钥
  if (key != NULL) {

    /// 拷贝一份 key 数据到本地
    memcpy(temp, key, 8);

    /// 将 key 压缩置换为 56 位
    permute(temp, DesTransform, 56);

    /// 将 key 分为两个 28 位
    memset(lkey, 0, 4);
    memset(rkey, 0, 4);

    for (j = 0; j < 28; j++) {
      bit_set(lkey, j, bit_get(temp, j));
      bit_set(rkey, j, bit_get(temp, j + 28));
    }

    /// 按照轮次计算子 key
    for (i = 0; i < 16; i++) {

      /// 根据子密钥的序列值旋转两组 key
      bit_rot_left(lkey, 28, DesRotations[i]);
      bit_rot_left(rkey, 28, DesRotations[i]);

      /// 重新合并各个组到一个 subkey
      for (j = 0; j < 28; j++) {
        bit_set(subkeys[i], j, bit_get(lkey, j));
        bit_set(subkeys[i], j + 28, bit_get(rkey, j));
      }

      /// 对重组后的密钥进行置换
      permute(subkeys[i], DesPermuted, 48);
    }
  }

  /// 拷贝一份源数据到本地
  memcpy(temp, source, 8);

  /// 执行初始置换
  permute(temp, DesInitial, 64);

  /// 将数据块分为两个 32 位的组
  memcpy(lblk, &temp[0], 4);
  memcpy(rblk, &temp[4], 4);

  /// 加密或者解密源数据
  for (i = 0; i < 16; i++) {

    /// 开始执行计算函数 f

    memcpy(fblk, rblk, 4);

    /// 执行扩展置换，将右数据从 32 位扩展到 48 位
    permute(fblk, DesExpansion, 48);

    /// 计算与这一轮的子密钥的异或值
    if (direction == encipher) {

      /// 如果是加密，子密钥按顺序执行
      bit_xor(fblk, subkeys[i], xblk, 48);

    } else {

      /// 如果是解密，子密钥按逆序执行
      bit_xor(fblk, subkeys[15 - i], xblk, 48);

    }
    
    memcpy(fblk, xblk, 6);

    /// 执行一系列的 S 盒替换操作

    p = 0;

    for (j = 0; j < 8; j++) {

      /// 计算 S 盒操作的行与列值
      row = (bit_get(fblk, (j * 6)+0) * 2) + (bit_get(fblk, (j * 6)+5) * 1);
      col = (bit_get(fblk, (j * 6)+1) * 8) + (bit_get(fblk, (j * 6)+2) * 4) +
            (bit_get(fblk, (j * 6)+3) * 2) + (bit_get(fblk, (j * 6)+4) * 1);

      /// 根据前面计算出的 6 位组执行 S 盒操作

      sblk = (unsigned char)DesSbox[j][row][col];

      for (k = 4; k < 8; k++) {

        bit_set(fblk, p, bit_get(&sblk, k));
        p++;
      }
    }

    /// 通过 P 盒来置换
    permute(fblk, DesPbox, 32);

    /// 就算左分组数据与函数 f 结果的异或值
    bit_xor(lblk, fblk, xblk, 32);

    /// 左右分组交换然后开始下一轮
    memcpy(lblk, rblk, 4);
    memcpy(rblk, xblk, 4);
  }

  /// 将最后的左右分组数据合并到结果数据
  memcpy(&target[0], rblk, 4);
  memcpy(&target[4], lblk, 4);

  /// 执行最终置换
  permute(target, DesFinal, 64);

  return 0;
}

#pragma mark - Public


void des_encipher(const unsigned char *plaintext, unsigned char *ciphertext,
                  const unsigned char *key)
{
  des_main(plaintext, ciphertext, key, encipher);
  return;
}


void des_decipher(const unsigned char *ciphertext, unsigned char *plaintext,
                  const unsigned char *key)
{
  des_main(ciphertext, plaintext, key, decipher);
  return;
}
