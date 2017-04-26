//
//  set.h
//  Algorithms - set
//
//  Created by YourtionGuo on 26/04/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#ifndef SET_H
#define SET_H

#include <stdlib.h>

#include "list.h"

/**
 集合
 */
typedef List Set;


/**
 初始化由参数 set 所指定的集合 - O(1)

 @param set 集合参数
 @param match 函数指针，用于判断两个成员是否相匹配
 @param destroy 成员析构函数（free...）
 */
void set_init(Set *set, int (*match)(const void *key1, const void *key2), void (*destroy)(void *data));


/**
 销毁 set 所指定的集合 - O(n)

 @param set 集合
 */
#define set_destroy list_destroy


/**
 在 set 所指定的集合中插入一个成员 - O(n)

 @param set 集合
 @param data 新成员
 @return 插入成功返回0; 已经存在返回1；否则返回-1
 */
int set_insert(Set *set, const void *data);


/**
 在 set 所指定的集合中移除数据域同 data 相吻合的成员 - O(n)

 @param set 集合
 @param data 被移除的成员的数据
 @return 移除成功返回0；否则返回-1
 */
int set_remove(Set *set, void **data);


/**
 建立一个集合，其结果为 set1 和 set2 所指定集合的并集 - O(mn)

 @param setu 新集合
 @param set1 集合1
 @param set2 集合2
 @return 成功返回0；否则返回-1
 */
int set_union(Set *setu, const Set *set1, const Set *set2);


/**
 建立一个集合，其结果为 set1 和 set2 所指定集合的交集 - O(mn)

 @param seti 新集合
 @param set1 集合1
 @param set2 集合2
 @return 成功返回0；否则返回-1
 */
int set_intersection(Set *seti, const Set *set1, const Set *set2);


/**
 建立一个集合，其结果为 set1 和 set2 所指定集合的差集 - O(mn)

 @param setd 集合
 @param set1 集合
 @param set2 集合
 @return 成功返回0；否则返回-1
 */
int set_difference(Set *setd, const Set *set1, const Set *set2);


/**
 判断由 data 所指定成员是否存在于set所指定的集合中 - O(n)

 @param set 集合
 @param data 所指定成员
 @return 找到成员返回1；否则返回-1
 */
int set_is_member(const Set *set, const void *data);


/**
 判断由参数 set1 所指定集合是否为参数 set2 所指定集合的子集 - O(mn)

 @param set1 集合1
 @param set2 集合2
 @return 子集返回1；否则返回-1
 */
int set_is_subset(const Set *set1, const Set *set2);


/**
 判断由参数 set1 所指定集合是否等于由参数 set2 所指定集合 - O(mn)

 @param set1 集合1
 @param set2 集合2
 @return 相等返回1；否则返回-1
 */
int set_is_equal(const Set *set1, const Set *set2);


/**
 返回由参数 set 所指定集合中的元素个数 - O(1)

 @param set 集合
 @return 集合大小
 */
#define set_size(set) ((set)->size)

#endif /* SET_H */
