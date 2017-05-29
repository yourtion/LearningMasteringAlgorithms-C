//
//  events.c
//  Algorithms - events
//
//  Created by YourtionGuo on 25/04/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <stdio.h>
#include <string.h>

#include "events.h"
#include "queue.h"

#pragma mark - Public


int receive_event(Queue *events, const Event *event)
{
  Event   *new_event;
  
  /// 创建事件对应存储空间
  if ((new_event = (Event *)malloc(sizeof(Event))) == NULL) return -1;
  
  /// 拷贝事件并入列
  memcpy(new_event, event, sizeof(Event));
  
  if (queue_enqueue(events, new_event) != 0) return -1;
  
  return 0;
}


int process_event(Queue *events, int (*dispatch)(Event *event))
{
  Event   *event;
  
  /// 如果没有事件待处理，返回 -1
  if (queue_size(events) == 0) return -1;
  
  /// 如果无法获取事件，返回 -1
  if (queue_dequeue(events, (void **)&event) != 0) return -1;
  
  dispatch(event);
  free(event);

  return 0;
}
