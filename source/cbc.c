//
//  cbc.c
//  Algorithms - DES in CBC mode
//
//  Created by YourtionGuo on 22/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <stdlib.h>

#include "bit.h"
#include "cbc.h"
#include "encrypt.h"

#pragma mark - Public

void cbc_encipher(const unsigned char *plaintext, unsigned char *ciphertext,
                  const unsigned char *key, int size)
{
  unsigned char   temp[8];
  int             i;

  /// 加密初始向量
  des_encipher(&plaintext[0], &ciphertext[0], key);

  /// 使用 CBC 模式执行 DES 加密
  i = 8;

  while (i < size) {

    bit_xor(&plaintext[i], &ciphertext[i - 8], temp, 64);
    des_encipher(temp, &ciphertext[i], NULL);
    i = i + 8;
  }

  return;
}


void cbc_decipher(const unsigned char *ciphertext, unsigned char *plaintext,
                  const unsigned char *key, int size)
{
  unsigned char   temp[8];
  int             i;

  /// 解密初始向量
  des_decipher(&ciphertext[0], &plaintext[0], key);

  /// 使用 CBC 模式执行 DES 解密
  i = 8;
  
  while (i < size) {
    
    des_decipher(&ciphertext[i], temp, NULL);
    bit_xor(&ciphertext[i - 8], temp, &plaintext[i], 64);
    i = i + 8;
  }
  
  return;
}
