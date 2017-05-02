//
//  ohtbl.h
//  Algorithms - open-addressed hash tables.
//
//  Created by YourtionGuo on 02/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#ifndef OHTBL_H
#define OHTBL_H

#include <stdlib.h>


/**
 开地址哈希表
 */
typedef struct OHTbl_
{
  int     positions;
  void    *vacated;
  
  int     (*h1)(const void *key);
  int     (*h2)(const void *key);
  int     (*match)(const void *key1, const void *key2);
  void    (*destroy)(void *data);
  
  int     size;
  void    **table;
  
} OHTbl;


/**
  初始化 htbl 指定的开地址哈希表 - O(m)，m 是哈希表中槽位的个数

 @param htbl 哈希表
 @param positions 槽位的个数
 @param h1 函数指针，用户定义的辅助哈希函数1
 @param h2 函数指针，用户定义的辅助哈希函数2
 @param match 函数指针，用于判断两个成员是否相匹配
 @param destroy 成员析构函数（free...）
 @return 初始化成功，返回0；否则返回-1
 */
int ohtbl_init(OHTbl *htbl, int positions,
               int (*h1)(const void *key),
               int (*h2)(const void *key),
               int (*match)(const void *key1, const void *key2),
               void (*destroy)(void *data));


/**
 销毁 htbl 指定的开地址哈希表 - O(m)
 
 @param htbl 哈希表
 */
void ohtbl_destroy(OHTbl *htbl);


/**
 向 htbl 指定的开地址哈希表中插入一个元素 - O(1)
 
 @param htbl 哈希表
 @param data 待插入元素
 @return 插入成功，返回0；已包含此元素，返回1；否则，返回-1
 */
int ohtbl_insert(OHTbl *htbl, const void *data);


/**
 从 htbl 指定的开地址哈希表中删除与 data 匹配的元素 - O(1)
 
 @param htbl 哈希表
 @param data 待删除元素
 @return 删除成功，返回0；否则，返回-1
 */
int ohtbl_remove(OHTbl *htbl, void **data);


/**
 判断由参数 htbl 指定的开地址哈希表中查找是否有与 data 相匹配的元素 - O(1)
 
 @param htbl 哈希表
 @param data 待查找元素
 @return 找到元素，返回0；否则，返回-1
 */
int ohtbl_lookup(const OHTbl *htbl, void **data);


/**
 返回由参数 htbl 指定的开地址哈希表中元素的个数 - O(1)
 
 @param htbl 哈希表
 @return 哈希表中元素的个数
 */
#define ohtbl_size(htbl) ((htbl)->size)

#endif /* OHTBL_H */
