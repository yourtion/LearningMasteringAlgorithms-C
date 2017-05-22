//
//  encrypt.h
//  Algorithms - Encrypt
//
//  Created by YourtionGuo on 22/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#ifndef ENCRYPT_H
#define ENCRYPT_H


/**
 采用 DES 算法将明文 plaintext 的一个 64 位的明文组加密 - O(1)

 @param plaintext 明文组
 @param ciphertext 返回的 64 位密文组
 @param key 指定64位的密钥
 */
void des_encipher(const unsigned char *plaintext, unsigned char *ciphertext,
                  const unsigned char *key);


/**
 采用 DES 算法将密文 ciphertext 的一个 64 位分组 - O(1)

 @param ciphertext 通过 des_encipher 加密过的密文
 @param plaintext 返回的 64 位明文分组
 @param key 指定64位的密钥（NULL 表示重用 des_encipher 的子密钥）
 */
void des_decipher(const unsigned char *ciphertext, unsigned char *plaintext,
                  const unsigned char *key);


/// 定义大数，在实际实现中需为 400 位以上的大数，Demo 中使用 unsigned long 替代
typedef unsigned long Huge;

/**
 RSA 公钥
 */
typedef struct RsaPubKey_
{
  Huge               e;
  Huge               n;

} RsaPubKey;

/**
 RSA 私钥
 */
typedef struct RsaPriKey_
{
  Huge               d;
  Huge               n;

} RsaPriKey;


/**
 采用 RSA 算法来加密由 plaintext 所指定的明文分组 - O(1)

 @param plaintext 明文组
 @param ciphertext 返回的密文组
 @param pubkey 公钥
 */
void rsa_encipher(Huge plaintext, Huge *ciphertext, RsaPubKey pubkey);


/**
 采用 RSA 算法来解密由 ciphertext 所指定的密文分组 - O(1)

 @param ciphertext 通过 rsa_encipher 加密过的密文
 @param plaintext 返回的明文分组
 @param prikey 私钥
 */
void rsa_decipher(Huge ciphertext, Huge *plaintext, RsaPriKey prikey);

#endif /* ENCRYPT_H */
