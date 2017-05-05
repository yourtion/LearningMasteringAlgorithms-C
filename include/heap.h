//
//  heap.h
//  Algorithms - Heap
//
//  Created by YourtionGuo on 05/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#ifndef HEAP_H
#define HEAP_H


/**
 堆
 */
typedef struct Heap_
{
  int     size;

  int     (*compare)(const void *key1, const void *key2);
  void    (*destroy)(void *data);

  void    **tree;

} Heap;


/**
 初始化由参数 heap 所指定堆 - O(1)

 @param heap 堆
 @param compare 函数指针，用于比较两个成员大小（大于返回 1，小于返回 -1，等于返回 0）
 @param destroy 成员析构函数（free...）
 */
void heap_init(Heap *heap,
               int (*compare)(const void *key1, const void *key2),
               void (*destroy)(void *data));


/**
 销毁由参数 heap 所指定堆 - O(n)

 @param heap 堆
 */
void heap_destroy(Heap *heap);


/**
 向堆 heap 中插入一个结点 - O(lg n)

 @param heap 堆
 @param data 结点数据
 @return 插入成功，返回0；否则返回-1
 */
int heap_insert(Heap *heap, const void *data);


/**
 从堆 heap 中释放堆顶部的结点 - O(lg n)

 @param heap 堆
 @param data 已释放结点的存储数据
 @return 释放成功，返回0；否则返回-1
 */
int heap_extract(Heap *heap, void **data);


/**
 由参数 heap 所指定堆中的结点个数 - O(1)

 @param heap 堆
 @return 结点个数
 */
#define heap_size(heap) ((heap)->size)

#endif /* HEAP_H */
