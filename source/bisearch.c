//
//  bisearch.c
//  Algorithms - Binary search
//
//  Created by YourtionGuo on 11/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <stdlib.h>
#include <string.h>

#include "search.h"

#pragma mark - Public

int bisearch(void *sorted, const void *target, int size, int esize,
             int(*compare)(const void *key1, const void *key2))
{
  int       left, middle, right;

  /// 持续执行搜索，直到 left 和 right 相交
  left = 0;
  right = size - 1;

  while (left <= right) {

    middle = (left + right) / 2;

    switch (compare(((char *)sorted + (esize * middle)), target)) {

      case -1:

        /// 准备向中间元素右方执行搜索
        left = middle + 1;
        break;

      case 1:

        /// 准备向中间元素左方执行搜索
        right = middle - 1;
        break;

      case 0:

        /// 将找到的元素索引返回
        return middle;

    }
  }

  /// 没找到元素返回 -1
  return -1;
}
