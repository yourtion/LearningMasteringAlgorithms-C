//
//  stack.c
//  Algorithms - stack
//
//  Created by YourtionGuo on 25/04/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <stdio.h>

#include "list.h"
#include "stack.h"

#pragma mark - Public


int stack_push(Stack *stack, const void *data)
{
  /// 将数据压入栈
  return list_ins_next(stack, NULL, data);
}


int stack_pop(Stack *stack, void **data)
{
  /// 弹出栈顶元素
  return list_rem_next(stack, NULL, data);
}
