//
//  rsa.c
//  Algorithms - RSA
//
//  Created by YourtionGuo on 22/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include "encrypt.h"

#pragma mark - Private


/**
 计算幂模 - 使用称为二进制平方-乘的算法

 @param a 明文分组
 @param b 公钥的 e 或 私钥的d
 @param n 公钥的 n 或 私钥的n
 @return 幂模结果
 */
static Huge modexp(Huge a, Huge b, Huge n)
{
  Huge        y;

  /// 使用二进制平方-乘的算法计算 a 的 b 次幂

  /// 寄存器 y 初始值为1
  y = 1;

  while (b != 0) {

    /// 每当遇到 b 中为 1 的位时，就将当前的 a 值乘上另一个寄存器 y
    if (b & 1) {
      y = (y * a) % n;
    }

    /// 对b的每个位执行平方操作
    a = (a * a) % n;

    /// 准备b的下一个位
    b = b >> 1;
  }

  return y;
}

#pragma mark - Public

void rsa_encipher(Huge plaintext, Huge *ciphertext, RsaPubKey pubkey)
{
  *ciphertext = modexp(plaintext, pubkey.e, pubkey.n);
  return;
}

void rsa_decipher(Huge ciphertext, Huge *plaintext, RsaPriKey prikey)
{
  *plaintext = modexp(ciphertext, prikey.d, prikey.n);
  return;
}
