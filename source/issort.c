//
//  issort.c
//  Algorithms - Insertion sort
//
//  Created by YourtionGuo on 10/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <stdlib.h>
#include <string.h>

#include "sort.h"

#pragma mark - Public


int issort(void *data, int size, int esize,
           int (*compare)(const void *key1, const void *key2))
{
  char      *a = data;
  void      *key;
  int       i, j;

  /// 创建存储当前元素空间
  if ((key = (char *)malloc(esize)) == NULL) return -1;

  /// 循环插入当前元素到已排序数组

  for (j = 1; j < size; j++) {

    memcpy(key, &a[j * esize], esize);
    i = j - 1;

    /// 确定当前元素插入位置
    while (i >= 0 && compare(&a[i * esize], key) > 0) {

      memcpy(&a[(i + 1) * esize], &a[i * esize], esize);
      i--;
    }

    memcpy(&a[(i + 1) * esize], key, esize);
  }

  /// 销毁排序所需空间
  free(key);
  
  return 0;
}
