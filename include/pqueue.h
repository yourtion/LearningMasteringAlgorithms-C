//
//  pqueue.h
//  Algorithms - priority queue
//
//  Created by YourtionGuo on 05/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#ifndef PQUEUE_H
#define PQUEUE_H

#include "heap.h"

/**
 优先队列
 */
typedef Heap PQueue;


/**
 初始化由参数 pqueue 所指定优先队列 - O(1)

 @param pqueue 优先队列
 @param compare 函数指针，用于比较两个成员优先级（高于返回 1，低于返回 -1，等于返回 0）
 @param destroy 成员析构函数（free...）
 */
#define pqueue_init heap_init


/**
 销毁由参数 pqueue 所指定优先队列 - O(n)

 @param pqueue 优先队列
 */
#define pqueue_destroy heap_destroy


/**
 在 pqueue 所指定的优先队列中插入一个元素 - O(lg n)

 @param pqueue 优先队列
 @param data 新成员
 @return 插入成功返回0; 已经存在返回1；否则返回-1
 */
#define pqueue_insert heap_insert


/**
 从优先队列 pqueue 中提取优先队列顶部的元素 - O(lg n)

 @param pqueue 优先队列
 @param data 已释放结点的存储数据
 @return 释放成功，返回0；否则返回-1
 */
#define pqueue_extract heap_extract


/**
 获取优先队列 pqueue 中优先级最高元素 - O(1)

 @param pqueue 优先队列
 @return 优先级最高的元素；如果队列为空，那么返回NULL
 */
#define pqueue_peek(pqueue) ((pqueue)->tree == NULL ? NULL : (pqueue)->tree[0])


/**
 优先队列中的元素个数 - O(1)

 @return 元素个数
 */
#define pqueue_size heap_size

#endif /* PQUEUE_H */
