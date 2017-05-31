//
//  hashpjw.c
//  Algorithms - hash function 
//
//  Created by YourtionGuo on 28/04/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include "hashpjw.h"

#pragma mark - Public


int hashpjw(const void *key)
{
  const char    *ptr;
  int           val;
  
  /// 通过一系列位操作对提供的 key 进行 hash
  
  val = 0;
  ptr = key;
  
  while (*ptr != '\0') {
    
    int tmp;
    val = (val << 4) + (*ptr);
    
    if ((tmp = (val & 0xf0000000))) {
      
      val = val ^ (tmp >> 24);
      val = val ^ tmp;
      
    }
    
    ptr++;
  }

  /// 根据实际情况将 PRIME_TBLSIZ 替换为需要的表大小
  return val % PRIME_TBLSIZ;
}
