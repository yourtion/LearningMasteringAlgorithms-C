//
//  bit.h
//  Algorithms - Bit operations
//
//  Created by YourtionGuo on 17/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#ifndef BIT_H
#define BIT_H


/**
 获取缓冲区 bits 中处于位置 pos 的位的状态 - O(1)

 @param bits 缓冲区
 @param pos 位置（缓冲区最左边的位置为 0 ）
 @return 状态值为 0 或 1
 */
int bit_get(const unsigned char *bits, int pos);


/**
 设置缓冲区 bits 中处于位置 pos 的位的状态为 state - O(1)

 @param bits 缓冲区
 @param pos 位置 (缓冲区最左边的位置为 0 )
 @param state 状态值（必须为 0 或 1 ）
 */
void bit_set(unsigned char *bits, int pos, int state);


/**
 按位计算两个缓冲区 bits1 与 bits2 的异或值 - O(β) β 为每个缓冲区中位的个数

 @param bits1 缓冲区 1
 @param bits2 缓冲区 2
 @param bitsx 计算结果
 @param size 每个缓冲区位个位
 */
void bit_xor(const unsigned char *bits1, const unsigned char *bits2, unsigned char *bitsx, int size);


/**
 轮转缓冲区 bits（含 size 位），将位值向左移 count 位 -　O(nβ) β 为每个缓冲区中位的个数，n 为要轮转到左边的位数

 @param bits 缓冲区
 @param size 缓冲区位个位
 @param count 左移位数
 */
void bit_rot_left(unsigned char *bits, int size, int count);

#endif /* BIT_H */
