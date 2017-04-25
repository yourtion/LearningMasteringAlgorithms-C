//
//  events.h
//  Algorithms - events
//
//  Created by YourtionGuo on 25/04/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#ifndef EVENTS_H
#define EVENTS_H

#include <stdlib.h>

#include "queue.h"

/**
 事件
 */
typedef struct Event_
{
  int   type;
  
} Event;


/**
 将要处理的事件入队 - O(1)

 @param events 事件队列
 @param event 事件
 @return 成功返回 0，否则返回 -1
 */
int receive_event(Queue *events, const Event *event);


/**
 事件从队列中出队 - O(1)

 @param events 事件队列
 @param dispatch 调度函数
 @return 成功返回 0，否则返回 -1
 */
int process_event(Queue *events, int (*dispatch)(Event *event));

#endif /* EVENTS_H */
