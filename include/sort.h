//
//  sort.h
//  Algorithms - sort algorithms
//
//  Created by YourtionGuo on 10/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#ifndef SORT_H
#define SORT_H


/**
 利用插入排序将数组 data 中的元素进行排序 - O(n^2)

 @param data 数据数组
 @param size 元素的个数
 @param esize 每个元素的大小
 @param compare 函数指针，用于比较两个成员大小（大于返回 1，小于返回 -1，等于返回 0）
 @return 成功返回 0；否则返回 -1
 */
int issort(void *data, int size, int esize,
           int (*compare)(const void *key1, const void *key2));


/**
 利用快速排序将数组 data 中的元素进行排序 - O(n lg n)

 @param data 数据数组
 @param size 元素的个数
 @param esize 每个元素的大小
 @param i 元素分区起点（默认 0 ）
 @param k 元素分区终点（默认 size-1 ）
 @param compare 函数指针，用于比较两个成员大小（大于返回 1，小于返回 -1，等于返回 0）
 @return 成功返回 0；否则返回 -1
 */
int qksort(void *data, int size, int esize, int i, int k,
           int (*compare)(const void *key1, const void *key2));



/**
 利用快速排序将数组 data 中的元素进行排序简化 - O(n lg n)

 @param data 数据数组
 @param size 元素的个数
 @param esize 每个元素的大小
 @param compare 函数指针，用于比较两个成员大小（大于返回 1，小于返回 -1，等于返回 0）
 @return 成功返回 0；否则返回 -1
 */
int qsrt(void *data, int size, int esize, int (*compare)(const void *key1, const void *key2));


/**
 利用归并排序将数组 data 中的元素进行排序 - O(n lg n)

 @param data 数据数组
 @param size 元素的个数
 @param esize 每个元素的大小
 @param i 元素分区起点（默认 0 ）
 @param k 元素分区终点（默认 size-1 ）
 @param compare 函数指针，用于比较两个成员大小（大于返回 1，小于返回 -1，等于返回 0）
 @return 成功返回 0；否则返回 -1
 */
int mgsort(void *data, int size, int esize, int i, int k,
           int (*compare)(const void *key1, const void *key2));

/**
 利用归并排序将数组 data 中的元素进行排序简化 - O(n lg n)

 @param data 数据数组
 @param size 元素的个数
 @param esize 每个元素的大小
 @param compare 函数指针，用于比较两个成员大小（大于返回 1，小于返回 -1，等于返回 0）
 @return 成功返回 0；否则返回 -1
 */
int mgsrt(void *data, int size, int esize, int (*compare)(const void *key1, const void *key2));


/**
 利用计数排序将数组 data 中的整数进行排序 - O(n+k)

 @param data 数据数组
 @param size 元素的个数
 @param k data 中最大的整数加1
 @return 成功返回 0；否则返回 -1
 */
int ctsort(int *data, int size, int k);


/**
 利用基数排序将数组 data 中的整数进行排序 - O(pn+pk)

 @param data 数据数组
 @param size 元素的个数
 @param p 每个整数包含的位数
 @param k 基数
 @return 成功返回 0；否则返回 -1
 */
int rxsort(int *data, int size, int p, int k);

#endif /* SORT_H */
