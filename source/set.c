//
//  set.c
//  Algorithms - set
//
//  Created by YourtionGuo on 26/04/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <stdio.h>

#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "set.h"

#pragma mark - Public


void set_init(Set *set, int (*match)(const void *key1, const void *key2), void (*destroy)(void *data))
{
  /// 初始化集合
  list_init(set, destroy);
  set->match = match;
  
  return;
}


int set_insert(Set *set, const void *data)
{
  /// 不允许插入已存在元素
  if (set_is_member(set, data)) return 1;
  
  /// 插入数据
  return list_ins_next(set, list_tail(set), data);
}


int set_remove(Set *set, void **data)
{
  ListElmt    *member, *prev;
  
  /// 查找待移除的元素
  prev = NULL;
  
  for (member = list_head(set); member != NULL; member = list_next(member)) {
    
    if (set->match(*data, list_data(member))) break;
    
    prev = member;
  }
  
  /// 找不到则返回 -1
  if (member == NULL) return -1;
  
  /// 移除成员
  return list_rem_next(set, prev, data);
}


int set_union(Set *setu, const Set *set1, const Set *set2)
{
  ListElmt    *member;
  void        *data;
  
  /// 初始化新集合
  set_init(setu, set1->match, NULL);
  
  /// 插入第一个集合的数据
  for (member = list_head(set1); member != NULL; member = list_next(member)) {
    
    data = list_data(member);
    
    if (list_ins_next(setu, list_tail(setu), data) != 0) {
      
      set_destroy(setu);
      return -1;
    }
    
  }
  
  /// 插入第二个集合的数据
  for (member = list_head(set2); member != NULL; member = list_next(member)) {
    
    if (set_is_member(set1, list_data(member))) {
      
      /// 不插入 set1 存在的元素
      continue;
      
    } else {
      
      data = list_data(member);
      
      if (list_ins_next(setu, list_tail(setu), data) != 0) {
        
        set_destroy(setu);
        return -1;
      }
    }
  }
  
  return 0;
}


int set_intersection(Set *seti, const Set *set1, const Set *set2)
{
  ListElmt    *member;
  void        *data;
  
  /// 初始化新集合
  set_init(seti, set1->match, NULL);
  
  /// 将两个集合都插入到集合中
  for (member = list_head(set1); member != NULL; member = list_next(member)) {
    
    if (set_is_member(set2, list_data(member))) {
      
      data = list_data(member);
      
      if (list_ins_next(seti, list_tail(seti), data) != 0) {
        
        set_destroy(seti);
        return -1;
        
      }
    }
  }
  
  return 0;
}


int set_difference(Set *setd, const Set *set1, const Set *set2)
{
  ListElmt    *member;
  void        *data;
  
  /// 初始化新集合
  set_init(setd, set1->match, NULL);
  
  /// 将在 set1 但是不在 set2 中的元素插入集合
  for (member = list_head(set1); member != NULL; member = list_next(member)) {
    
    if (!set_is_member(set2, list_data(member))) {
      
      data = list_data(member);
      
      if (list_ins_next(setd, list_tail(setd), data) != 0) {
        
        set_destroy(setd);
        return -1;
        
      }
    }
  }
  
  return 0;
}


int set_is_member(const Set *set, const void *data)
{
  ListElmt      *member;
  
  /// 判断元素是否在集合内
  for (member = list_head(set); member != NULL; member = list_next(member)) {
    
    if (set->match(data, list_data(member))) return 1;
    
  }
  
  return 0;
}


int set_is_subset(const Set *set1, const Set *set2)
{
  ListElmt      *member;
  
  /// 快速判断，先判断集合大小
  if (set_size(set1) > set_size(set2)) return 0;
  
  /// 判断 set1 元素是否在 set2 中
  for (member = list_head(set1); member != NULL; member = list_next(member)) {
    
    if (!set_is_member(set2, list_data(member))) return 0;
    
  }
  
  return 1;
}


int set_is_equal(const Set *set1, const Set *set2)
{
  /// 快速判断，先判断集合大小
  if (set_size(set1) != set_size(set2)) return 0;
  
  /// 如果集合大小相等，那么子集就是本身
  return set_is_subset(set1, set2);
}
