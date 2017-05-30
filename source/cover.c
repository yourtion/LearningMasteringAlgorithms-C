//
//  cover.c
//  Algorithms - set covering
//
//  Created by YourtionGuo on 26/04/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <stdlib.h>

#include "cover.h"
#include "list.h"
#include "set.h"

#pragma mark - Public


int cover(Set *members, Set *subsets, Set *covering)
{
  Set       intersection;
  KSet      *subset;
  ListElmt  *member, *max_member = NULL;
  void      *data;
  int       max_size;
  
  /// 初始化覆盖集合
  set_init(covering, subsets->match, NULL);
 
  /// 当还有成员未覆盖同时还有候选集合成员
  while (set_size(members) > 0 && set_size(subsets) > 0) {
    
    ///找到覆盖最多成员的子集
    
    max_size = 0;
    
    for (member = list_head(subsets); member != NULL; member = list_next(member)) {
      
      if (set_intersection(&intersection, &((KSet *)list_data(member))->set, members) != 0) return -1;
      
      if (set_size(&intersection) > max_size) {
        
        max_member = member;
        max_size = set_size(&intersection);
        
      }
      
      set_destroy(&intersection);
    }
    
    /// 如果没有交集则不可能覆盖
    if (max_size == 0) return 1;
    
    
    /// 插入选中的子集到覆盖集合
    subset = (KSet *)list_data(max_member);
    
    if (set_insert(covering, subset) != 0) return -1;
    
    /// 从待覆盖集合移除已覆盖成员
    for (member = list_head(&((KSet *)list_data(max_member))->set); member != NULL; member = list_next(member)) {
      
      data = list_data(member);
      
      if (set_remove(members, (void**)&data) == 0 && members->destroy != NULL) members->destroy(data);
      
    }
    
    /// 从候选人集合移除已选中子集
    if (set_remove(subsets, (void **)&subset) != 0) return -1;
  }
  
  /// 如果还有未覆盖成员则不可能覆盖
  if (set_size(members) > 0) return -1;
  
  return 0;
}
