//
//  stack.h
//  Algorithms - stack
//
//  Created by YourtionGuo on 25/04/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

#include "list.h"

/**
 栈
 */
typedef List Stack;


/**
 初始化 stack 指定的栈 - O(1)

 @param stack 栈
 @param destroy 成员析构函数（free...）
 */
#define stack_init list_init


/**
 销毁 stack 指定的栈 - O(n)

 @param stack 栈
 */
#define stack_destroy list_destroy


/**
 向 stack 指定的栈中压入一个元素 - O(1)

 @param stack 栈
 @param data 被压入数据
 @return 成功返回 0，否则返回 -1
 */
int stack_push(Stack *stack, const void *data);


/**
 从 stack 指定的栈中弹出一个元素 - O(1)

 @param stack 栈
 @param data 已弹出元素中存储的数据
 @return 成功返回 0，否则返回 -1
 */
int stack_pop(Stack *stack, void **data);


/**
 获取 stack 指定的栈顶部元素中存储的数据 - O(1)

 @param stack 栈
 @return 栈顶存储的数据
 */
#define stack_peek(stack) ((stack)->head == NULL ? NULL : (stack)->head->data)


/**
 栈中元素的个数 - O(1)

 @return 栈中元素的个数
 */
#define stack_size list_size

#endif /* STACK_H */
