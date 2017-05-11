//
//  search.h
//  Algorithms - Search
//
//  Created by YourtionGuo on 11/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#ifndef SEARCH_H
#define SEARCH_H


/**
 二分查找 - O(lg n)

 @param sorted 已排序数据
 @param target 查找目标
 @param size 元素个数
 @param esize 每个元素的大小
 @param compare 函数指针，用于比较两个成员大小（大于返回 1，小于返回 -1，等于返回 0）
 @return 查找成功返回目标的索引值；否则，返回-1
 */
int bisearch(void *sorted, const void *target, int size, int esize,
             int(*compare)(const void *key1, const void *key2));

#endif /* SEARCH_H */
