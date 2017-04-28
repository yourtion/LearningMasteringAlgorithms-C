//
//  chtbl.h
//  Algorithms - chained hash table
//
//  Created by YourtionGuo on 28/04/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#ifndef CHTBL_H
#define CHTBL_H

#include <stdlib.h>

#include "list.h"


/**
 链式哈希表
 */
typedef struct CHTbl_
{
  int     buckets;
  
  int     (*h)(const void *key);
  int     (*match)(const void *key1, const void *key2);
  void    (*destroy)(void *data);
  
  int     size;
  List    *table;
  
} CHTbl;


/**
 初始化 htbl 指定的链式哈希表 - O(m)，m 是哈希表中“桶”的个数

 @param htbl 哈希表
 @param buckets 所分配的“桶”的个数
 @param h 函数指针，用户定义的哈希函数
 @param match 函数指针，用于判断两个成员是否相匹配
 @param destroy 成员析构函数（free...）
 @return 表初始化成功，返回0；否则返回-1
 */
int chtbl_init(CHTbl *htbl, int buckets,
               int (*h)(const void *key),
               int (*match)(const void *key1, const void *key2),
               void (*destroy)(void *data));


/**
 销毁 htbl 指定的链式哈希表 - O(m)

 @param htbl 哈希表
 */
void chtbl_destroy(CHTbl *htbl);


/**
 向 htbl 指定的链式哈希表中插入一个元素 - O(1)

 @param htbl 哈希表
 @param data 待插入元素
 @return 插入成功，返回0；已包含此元素，返回1；否则，返回-1
 */
int chtbl_insert(CHTbl *htbl, const void *data);


/**
 从 htbl 指定的链式哈希表中删除与 data 匹配的元素 - O(1)

 @param htbl 哈希表
 @param data 待删除元素
 @return 删除成功，返回0；否则，返回-1
 */
int chtbl_remove(CHTbl *htbl, void **data);


/**
 判断由参数 htbl 指定的链式哈希表中查找是否有与 data 相匹配的元素 - O(1)

 @param htbl 哈希表
 @param data 待查找元素
 @return 找到元素，返回0；否则，返回-1
 */
int chtbl_lookup(const CHTbl *htbl, void **data);


/**
 返回由参数 htbl 指定的链式哈希表中元素的个数 - O(1)

 @param htbl 哈希表
 @return 哈希表中元素的个数
 */
#define chtbl_size(htbl) ((htbl)->size)

#endif /* CHTBL_H */
