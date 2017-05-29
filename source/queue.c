//
//  queue.c
//  Algorithms - queue
//
//  Created by YourtionGuo on 25/04/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include "list.h"
#include "queue.h"

#pragma mark - Public


int queue_enqueue(Queue *queue, const void *data)
{
  /// 入队
  return list_ins_next(queue, list_tail(queue), data);
}


int queue_dequeue(Queue *queue, void **data)
{
  /// 出队
  return list_rem_next(queue, NULL, data);
}
