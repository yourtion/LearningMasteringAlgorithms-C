//
//  mgsort.c
//  Algorithms - Merge sort
//
//  Created by YourtionGuo on 11/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <stdlib.h>
#include <string.h>

#include "sort.h"

#pragma mark - Private


/**
 将两个有序集合并成一个有序集

 @param data 数据数组
 @param esize 每个元素的大小
 @param i 元素分区起点
 @param j 元素中间元素位置
 @param k 元素分区终点
 @param compare 函数指针，用于比较两个成员大小（大于返回 1，小于返回 -1，等于返回 0）
 @return 成功返回 0；否则返回 -1
 */
static int merge(void *data, int esize, int i, int j, int k,
                 int (*compare)(const void *key1, const void *key2))
{
  char      *a = data, *m;
  int       ipos, jpos, mpos;

  /// 初始化合并过程使用的计数器
  ipos = i;
  jpos = j + 1;
  mpos = 0;

  /// 创建用于合并数组的空间
  if ((m = (char *)malloc(esize * ((k - i) + 1))) == NULL) return -1;

  /// 执行合并直到没有数据

  while (ipos <= j || jpos <= k) {

    if (ipos > j) {

      /// 左半部分还有元素
      while (jpos <= k) {

        memcpy(&m[mpos * esize], &a[jpos * esize], esize);
        jpos++;
        mpos++;
      }

      continue;

    } else if (jpos > k) {

      /// 右半部分还有元素
      while (ipos <= j) {

        memcpy(&m[mpos * esize], &a[ipos * esize], esize);
        ipos++;
        mpos++;

      }

      continue;
    }

    /// 添加下一个元素到已排序数组

    if (compare(&a[ipos * esize], &a[jpos * esize]) < 0) {

      memcpy(&m[mpos * esize], &a[ipos * esize], esize);
      ipos++;
      mpos++;

    } else {

      memcpy(&m[mpos * esize], &a[jpos * esize], esize);
      jpos++;
      mpos++;

    }
  }

  /// 将已排序数据放回
  memcpy(&a[i * esize], m, esize * ((k - i) + 1));

  /// 销毁用于排序的临时空间
  free(m);

  return 0;
}

#pragma mark - Public


int mgsort(void *data, int size, int esize, int i, int k,
           int (*compare)(const void *key1, const void *key2))
{
  int       j;

  /// 当没有元素可以分割则停止递归
  if (i < k) {

    /// 确定元素分割点
    j = (int)(((i + k - 1)) / 2);

    /// 递归对两部分执行归并排序
    if (mgsort(data, size, esize, i, j, compare) < 0) return -1;
    if (mgsort(data, size, esize, j + 1, k, compare) < 0) return -1;

    /// 合并两个已排序白部分
    if (merge(data, esize, i, j, k, compare) < 0) return -1;
    
  }
  
  return 0;
}

int mgsrt(void *data, int size, int esize, int (*compare)(const void *key1, const void *key2)) {
  return mgsort(data, size, esize, 0, size - 1, compare);
}

