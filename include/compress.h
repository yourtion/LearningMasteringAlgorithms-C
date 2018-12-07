//
//  compress.h
//  Algorithms - Huffman and LZ77（Lempel-Ziv-1977） compress
//
//  Created by YourtionGuo on 17/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#ifndef COMPRESS_H
#define COMPRESS_H

#include "bitree.h"


/**
 霍夫曼树结点
 */
typedef struct HuffNode_
{
  unsigned char   symbol;
  int             freq;

} HuffNode;


/**
 霍夫曼编码表
 */
typedef struct HuffCode_
{
  unsigned char     used;
  unsigned short    code;
  unsigned char     size;

} HuffCode;


/**
 用霍夫曼编码的方法压缩缓冲区 original 中的数据 - O(n) n 是原始数据中符号的个数

 @param original 原始数据缓冲区
 @param compressed 压缩后的数据
 @param size 缓冲区包含字节
 @return 压缩数据成功返回压缩后数据的字节数；否则，返回-1
 */
int huffman_compress(const unsigned char *original, unsigned char **compressed, int size);


/**
 用霍夫曼编码的方法解压缩缓冲区 compressed 中的数据 - O(n) n 是原始数据中符号的个数

 @param compressed 压缩缓冲区
 @param original 恢复后数据
 @return 解压缩数据成功返回恢复后数据的字节数；否则，返回-1
 */
int huffman_uncompress(const unsigned char *compressed, unsigned char **original);


/// 类型长度
#define     LZ77_TYPE_BITS        1
/// 滑动窗口偏移量长度
#define     LZ77_WINOFF_BITS     12
/// 短语标志长度
#define     LZ77_BUFLEN_BITS      5
/// 下一个匹配符号长度
#define     LZ77_NEXT_BITS        8

/// 滑动窗口的大小
#define     LZ77_WINDOW_SIZE   4096
/// 前向缓冲区大小
#define     LZ77_BUFFER_SIZE     32

/// LZ77短语长度
#define     LZ77_PHRASE_BITS    (LZ77_TYPE_BITS+LZ77_WINOFF_BITS+LZ77_NEXT_BITS+LZ77_BUFLEN_BITS)

/// LZ77符号长度
#define     LZ77_SYMBOL_BITS    (LZ77_TYPE_BITS+LZ77_NEXT_BITS)
#define LZ77_SYNBOL_BITS (LZ77_TYPE_BITS+LZ77_NEXT_BITS)


/**
 用 LZ77 算法压缩缓冲区 original 中的数据 - O(n) n 是原始数据中符号的个数

 @param original 原始数据缓冲区
 @param compressed 压缩后的数据
 @param size 缓冲区包含字节
 @return 压缩数据成功返回压缩后数据的字节数；否则，返回-1
 */
int lz77_compress(const unsigned char *original, unsigned char **compressed, int size);


/**
 用 LZ77 算法解压缩缓冲区 compressed 中的数据 - O(n) n 是原始数据中符号的个数

 @param compressed 压缩缓冲区
 @param original 恢复后数据
 @return 解压缩数据成功返回恢复后数据的字节数；否则，返回-1
 */
int lz77_uncompress(const unsigned char *compressed, unsigned char **original);

#endif /* COMPRESS_H */
