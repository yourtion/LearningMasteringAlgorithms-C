//
//  ctsort.c
//  Algorithms - Counting sort
//
//  Created by YourtionGuo on 11/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <stdlib.h>
#include <string.h>

#include "sort.h"

#pragma mark - Public

int ctsort(int *data, int size, int k)
{
  int       *counts, *temp;
  int       i, j;

  /// 初始化 counts 数组空间
  if ((counts = (int *)malloc(k * sizeof(int))) == NULL)return -1;

  /// 初始化空间用于排序结果
  if ((temp = (int *)malloc(size * sizeof(int))) == NULL) return -1;

  /// 初始化 counts
  for (i = 0; i < k; i++) {
    counts[i] = 0;
  }

  /// 计算元素出现个数
  for (j = 0; j < size; j++)
    counts[data[j]] = counts[data[j]] + 1;

  /// 调整计数值，加上前一个元素出现次数
  for (i = 1; i < k; i++) {
    counts[i] = counts[i] + counts[i - 1];
  }

  /// 使用 counts 将元素放到对应位置
  for (j = size - 1; j >= 0; j--) {

    temp[counts[data[j]] - 1] = data[j];
    counts[data[j]] = counts[data[j]] - 1;
  }

  /// 将已排序数据放回
  memcpy(data, temp, size * sizeof(int));

  /// 销毁用于排序的临时空间
  free(counts);
  free(temp);
  
  return 0;
}

