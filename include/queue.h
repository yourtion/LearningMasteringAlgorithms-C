//
//  queue.h
//  Algorithms - queue
//
//  Created by YourtionGuo on 25/04/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>

#include "list.h"

/**
 队列
 */
typedef List Queue;

/**
 初始化 queue 指定的队列 - O(1)
 
 @param queue 队列
 @param destroy 成员析构函数（free...）
 */
#define queue_init list_init


/**
 销毁 queue 指定的队列 - O(n)
 
 @param queue 队列
 */
#define queue_destroy list_destroy


/**
 向 queue 指定的队列末尾中插入一个元素 - O(1)

 @param queue 队列
 @param data 待插入元素
 @return 成功返回 0，否则返回 -1
 */
int queue_enqueue(Queue *queue, const void *data);


/**
 从 queue 指定的队列头部删除一个元素 - O(1)

 @param queue 队列
 @param data 出队元素中存储的数据
 @return 成功返回 0，否则返回 -1
 */
int queue_dequeue(Queue *queue, void **data);


/**
 获取由 queue 指定的队列头部元素中存储数据 - O(1)

 @param queue 队列
 @return 队列头部元素中存储的数据
 */
#define queue_peek(queue) ((queue)->head == NULL ? NULL : (queue)->head->data)


/**
 获取由 queue 指定的队列元素个数 - O(1)

 @return 队列元素个数
 */
#define queue_size list_size

#endif /* QUEUE_H */
