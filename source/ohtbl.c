//
//  ohtbl.c
//  Algorithms - open-addressed hash tables.
//
//  Created by YourtionGuo on 02/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ohtbl.h"

/// 哨兵元素，用于指明新元素将要插入的槽位。
static char        vacated;

#pragma mark - Public


int ohtbl_init(OHTbl *htbl, int positions,
               int (*h1)(const void *key),
               int (*h2)(const void *key),
               int (*match)(const void *key1, const void *key2),
               void (*destroy)(void *data))
{
  int     i;
  
  if ((htbl->table = (void **)malloc(positions * sizeof(void *))) == NULL) return -1;
  
  /// 创建 hash 表所需空间
  htbl->positions = positions;
  
  for (i = 0; i < htbl->positions; i++) {
    htbl->table[i] = NULL;
  }
  
  /// 设置哨兵元素
  htbl->vacated = &vacated;
  
  /// 封装函数进 hash 表
  htbl->h1 = h1;
  htbl->h2 = h2;
  htbl->match = match;
  htbl->destroy = destroy;
  
  /// 初始化表大小为 0
  htbl->size = 0;
  
  return 0;
}


void ohtbl_destroy(OHTbl *htbl)
{
  int     i;
  
  if (htbl->destroy != NULL) {
    
    /// 调用用户定义 destroy 方法删除元素
    for (i = 0; i < htbl->positions; i++) {
      
      if (htbl->table[i] != NULL && htbl->table[i] != htbl->vacated) {
        
        htbl->destroy(htbl->table[i]);
      }
    }
  }
  
  /// 清理 hash 表空间
  free(htbl->table);
  
  /// 清理 hash 表结构体数据
  memset(htbl, 0, sizeof(OHTbl));
  
  return;
}


int ohtbl_insert(OHTbl *htbl, const void *data)
{
  void      *temp;
  int       position, i;
  
  /// 如果没有空间，返回 -1
  if (htbl->size == htbl->positions) return -1;
  
  /// 如果元素已经存在返回 1
  temp = (void *)data;
  if (ohtbl_lookup(htbl, &temp) == 0) return 1;
  
  /// 使用双重 hash 对元素计算 key
  for (i = 0; i < htbl->positions; i++) {
    
    position = (htbl->h1(data) + (i * htbl->h2(data))) % htbl->positions;
    
    if (htbl->table[position] == NULL || htbl->table[position] == htbl->vacated) {
      
      /// 将数据插入到表中
      htbl->table[position] = (void *)data;
      htbl->size++;
      return 0;
    }
  }
  
  /// 找不到合适的槽位返回 -1
  return -1;
  
}


int ohtbl_remove(OHTbl *htbl, void **data)
{
  int     position, i;
  
  /// 使用双重 hash 对元素计算 key
  for (i = 0; i < htbl->positions; i++) {
    
    position = (htbl->h1(*data) + (i * htbl->h2(*data))) % htbl->positions;
    
    /// 如果没找到返回 -1
    if (htbl->table[position] == NULL) return -1;
      
    if (htbl->table[position] == htbl->vacated) {
      
      /// 找到哨兵元素则继续
      continue;
      
    } else if (htbl->match(htbl->table[position], *data)) {
      
      /// 将找到的元素放入 data
      *data = htbl->table[position];
      htbl->table[position] = htbl->vacated;
      htbl->size--;
      return 0;
      
    }
  }
  
  /// 如果没找到返回 -1
  return -1;
}


int ohtbl_lookup(const OHTbl *htbl, void **data)
{
  int     position, i;
  
  /// 使用双重 hash 对元素计算 key
  for (i = 0; i < htbl->positions; i++) {
    
    position = (htbl->h1(*data) + (i * htbl->h2(*data))) % htbl->positions;
    
    if (htbl->table[position] == NULL) return -1;
    
    
    if (htbl->match(htbl->table[position], *data)) {
      
      /// 将找到的元素放入 data
      *data = htbl->table[position];
      return 0;
      
    }
  }
  
  /// 如果没找到返回 -1
  return -1;
}
