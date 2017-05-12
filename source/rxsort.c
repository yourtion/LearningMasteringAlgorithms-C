//
//  rxsort.c
//  Algorithms - Radix sort
//
//  Created by YourtionGuo on 11/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "sort.h"

#pragma mark - Public

int rxsort(int *data, int size, int p, int k)
{
  int       *counts, *temp;
  int       index, pval, i, j, n;

  /// 初始化 counts 空间
  if ((counts = (int *)malloc(k * sizeof(int))) == NULL) return -1;

  /// 初始化空间用于排序结果
  if ((temp = (int *)malloc(size * sizeof(int))) == NULL) return -1;

  /// 从低位到高位对数据进行排序
  for (n = 0; n < p; n++) {

    /// 初始化 counts

    for (i = 0; i < k; i++) {
      counts[i] = 0;
    }

    /// 计算当前位数值
    pval = (int)pow((double)k, (double)n);

    /// 对当前位置进行计数
    for (j = 0; j < size; j++) {

      index = (int)(data[j] / pval) % k;
      counts[index] = counts[index] + 1;
    }

    /// 调整计数值，加上前一个元素出现次数
    for (i = 1; i < k; i++) {
      counts[i] = counts[i] + counts[i - 1];
    }

    /// 使用 counts 将元素放到对应位置

    for (j = size - 1; j >= 0; j--) {

      index = (int)(data[j] / pval) % k;
      temp[counts[index] - 1] = data[j];
      counts[index] = counts[index] - 1;
    }

    /// 将当前已排序数据放回
    memcpy(data, temp, size * sizeof(int));
  }

  /// 销毁用于排序的临时空间
  free(counts);
  free(temp);
  
  return 0;
}
