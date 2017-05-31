//
//  chtbl.c
//  Algorithms - chained hash table 
//
//  Created by YourtionGuo on 28/04/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "chtbl.h"

#pragma mark - Public


int chtbl_init(CHTbl *htbl, int buckets,
               int (*h)(const void *key),
               int (*match)(const void *key1, const void *key2),
               void (*destroy)(void *data))
{
  
  int     i;
  
  /// 创建 hash 表所需空间
  if ((htbl->table = (List *)malloc(buckets * sizeof(List))) == NULL) return -1;
  
  /// 初始化 buckets
  htbl->buckets = buckets;
  
  for (i = 0; i < htbl->buckets; i++) {
    list_init(&htbl->table[i], destroy);
  }
  
  /// 封装函数进 hash 表
  htbl->h = h;
  htbl->match = match;
  htbl->destroy = destroy;
  
  /// 初始化表大小为 0
  htbl->size = 0;
  
  return 0;
}


void chtbl_destroy(CHTbl *htbl)
{
  
  int     i;
  
  /// 删除 buckets
  for (i = 0; i < htbl->buckets; i++) {
    list_destroy(&htbl->table[i]);
  }
  
  /// 清理 hash 表空间
  free(htbl->table);
  /// 清理 hash 表结构体数据
  memset(htbl, 0, sizeof(CHTbl));
  
  return;
}


int chtbl_insert(CHTbl *htbl, const void *data)
{
  
  void      *temp;
  int     bucket, retval;
  
  /// 如果元素已经存在返回 1
  temp = (void *)data;
  
  if (chtbl_lookup(htbl, &temp) == 0) return 1;
  
  /// 计算 hash
  bucket = htbl->h(data) % htbl->buckets;
  
  /// 插入到相应的 bucket
  if ((retval = list_ins_next(&htbl->table[bucket], NULL, data)) == 0) {
    htbl->size++;
  }
  
  return retval;
}


int chtbl_remove(CHTbl *htbl, void **data)
{
  
  ListElmt      *element, *prev;
  int           bucket;
  
  /// 计算 hash
  bucket = htbl->h(*data) % htbl->buckets;
  
  /// 在 bucket 中查找数据
  prev = NULL;
  
  for (element = list_head(&htbl->table[bucket]); element != NULL; element = list_next(element)) {
    
    if (htbl->match(*data, list_data(element))) {
      
      /// 从 bucket 中移除找到的元素
      if (list_rem_next(&htbl->table[bucket], prev, data) != 0) return -1;
        
      htbl->size--;
      return 0;
      
    }
    prev = element;
    
  }
  
  /// 如果没找到返回 -1
  return -1;
}


int chtbl_lookup(const CHTbl *htbl, void **data) {
  
  ListElmt      *element;
  int           bucket;
  
  /// 计算 hash
  bucket = htbl->h(*data) % htbl->buckets;
  
  /// 在 bucket 中查找数据
  for (element = list_head(&htbl->table[bucket]); element != NULL; element = list_next(element)) {
    
    if (htbl->match(*data, list_data(element))) {
      
      /// 返回找到的数据
      *data = list_data(element);
      return 0;
      
    }
  }
  
  /// 如果没找到返回 -1
  return -1;
}
