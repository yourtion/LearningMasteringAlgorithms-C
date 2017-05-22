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

/*****************************************************************************
 *                                                                            *
 *  In a secure implementation, Huge should be at least 400 decimal digits,   *
 *  instead of the 10 below (ULONG_MAX = 4294967295).                         *
 *                                                                            *
 *****************************************************************************/

typedef unsigned long Huge;

/*****************************************************************************
 *                                                                            *
 *  Define a structure for RSA public keys.                                   *
 *                                                                            *
 *****************************************************************************/

typedef struct RsaPubKey_ {

  Huge               e;
  Huge               n;

} RsaPubKey;

/*****************************************************************************
 *                                                                            *
 *  Define a structure for RSA private keys.                                  *
 *                                                                            *
 *****************************************************************************/

typedef struct RsaPriKey_ {

  Huge               d;
  Huge               n;

} RsaPriKey;

void rsa_encipher(Huge plaintext, Huge *ciphertext, RsaPubKey pubkey);

void rsa_decipher(Huge ciphertext, Huge *plaintext, RsaPriKey prikey);

#endif /* ENCRYPT_H */
