//
//  cover.h
//  Algorithms - set covering
//
//  Created by YourtionGuo on 26/04/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#ifndef COVER_H
#define COVER_H

#include "set.h"


/**
 带 key 的集合
 */
typedef struct KSet_
{
  void      *key;
  Set       set;
  
} KSet;


/**
 计算集合覆盖

 @param members 待覆盖集合成员
 @param subsets 候选人集合
 @param covering 覆盖集合C结果
 @return 找到覆盖返回0; 不可能实现完全覆盖返回1；其他情况返回-1
 */
int cover(Set *members, Set *subsets, Set *covering);

#endif /* COVER_H */
