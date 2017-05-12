//
//  qksort.c
//  Algorithms - Quicksort
//
//  Created by YourtionGuo on 10/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "sort.h"

#pragma mark - Private


/**
 比较两个整数（用于三位数取中值）

 @param int1 整数 1
 @param int2 整数 2
 @return 大于返回 1，小于返回 -1，等于返回 0
 */
static int compare_int(const void *int1, const void *int2)
{
  if (*(const int *)int1 > *(const int *)int2) return 1;
  if (*(const int *)int1 < *(const int *)int2) return -1;
  return 0;
}


/**
 分区排序函数

 @param data 数据数组
 @param esize 每个元素的大小
 @param i 元素分区起点
 @param k 元素分区终点
 @param compare 函数指针，用于比较两个成员大小（大于返回 1，小于返回 -1，等于返回 0）
 @return 成功返回 0；否则返回 -1
 */
static int partition(void *data, int esize, int i, int k,
                     int (*compare)(const void *key1, const void *key2))
{
  char      *a = data;
  void      *pval, *temp;
  int       r[3];

  /// 初始化分区元素和临时空间

  if ((pval = malloc(esize)) == NULL) return -1;

  if ((temp = malloc(esize)) == NULL) {

    free(pval);
    return -1;
  }

  /// 使用中位数法找分区值
  r[0] = (rand() % (k - i + 1)) + i;
  r[1] = (rand() % (k - i + 1)) + i;
  r[2] = (rand() % (k - i + 1)) + i;
  issort(r, 3, sizeof(int), compare_int);
  memcpy(pval, &a[r[1] * esize], esize);

  /// 在分区元素周围创建分区空间
  i--;
  k++;

  while (1) {

    /// 将 k 往左边移动，直到找到一个小于或等于分割值的元素
    do {
      k--;
    } while (compare(&a[k * esize], pval) > 0);

    /// 将 i 往右边移动，直到找到一个大于或等于分割值的元素
    do {
      i++;
    } while (compare(&a[i * esize], pval) < 0);

    if (i >= k) {
      /// 当 i 跟 k 重合或者交叉时排序完成
      break;

    } else {

      /// 交换找到元素的位置
      memcpy(temp, &a[i * esize], esize);
      memcpy(&a[i * esize], &a[k * esize], esize);
      memcpy(&a[k * esize], temp, esize);

    }
  }

  /// 销毁排序所需空间
  free(pval);
  free(temp);

  /// 返回区分分区的位置
  return k;
}

#pragma mark - Public


int qksort(void *data, int size, int esize, int i, int k,
           int (*compare)(const void *key1, const void *key2))
{
  int       j;

  /// 当已经不能进行分区时排序结束

  if (i < k) {

    /// 确定分区位置
    if ((j = partition(data, esize, i, k, compare)) < 0) return -1;

    /// 递归处理右半部分
    if (qksort(data, size, esize, i, j, compare) < 0) return -1;

    /// 递归处理右半部分
    if (qksort(data, size, esize, j + 1, k, compare) < 0) return -1;
    
  }
  
  return 0;
}

int qsrt(void *data, int size, int esize, int (*compare)(const void *key1, const void *key2)) {
  srand(getpid());
  return qksort(data, size, esize, 0, size - 1, compare);
}
