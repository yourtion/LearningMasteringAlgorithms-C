//
//  cbc.h
//  Algorithms - DES in CBC mode
//
//  Created by YourtionGuo on 22/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#ifndef CBC_H
#define CBC_H


/**
 采用 DES 算法中的 CBC 模式来对缓冲区中的数据做加密操作 - O(n) n 为加密或解密的分组数量

 @param plaintext 明文缓冲区
 @param ciphertext 加密后数据
 @param key 密钥
 @param size 缓冲区字节大小
 */
void cbc_encipher(const unsigned char *plaintext, unsigned char *ciphertext,
                  const unsigned char *key, int size);


/**
 采用 DES 算法中的 CBC 模式来对缓冲区中的数据做解密操作 - O(n)
 
 @param ciphertext 密文缓冲区
 @param plaintext 解密后数据
 @param key 密钥
 @param size 缓冲区字节大小
 */
void cbc_decipher(const unsigned char *ciphertext, unsigned char *plaintext,
                  const unsigned char *key, int size);

#endif /* CBC_H */
