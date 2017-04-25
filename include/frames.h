//
//  frames.h
//  Algorithms - frame
//
//  Created by YourtionGuo on 24/04/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#ifndef FRAMES_H
#define FRAMES_H

#include "list.h"


/**
 从空闲页帧链表中获取空闲页帧号

 @param frames 帧链表
 @return 页帧号
 */
int alloc_frame(List *frames);



/**
 释放之前获取的页帧号

 @param frames 帧链表
 @param frame_number 页帧号
 @return 成功返回 0，否则返回 -1
 */
int free_frame(List *frames, int frame_number);

#endif /* FRAMES_H */
