//
//  frames.c
//  Algorithms - frame
//
//  Created by YourtionGuo on 24/04/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <stdio.h>
#include "frames.h"
#include "list.h"

#pragma mark - Public


int alloc_frame(List *frames)
{
  int frame_number, *data;
  if (list_size(frames) == 0) {
    /// 如果 frames 没有空间，返回错误
    return -1;
  } else {
    if (list_rem_next(frames, NULL, (void **)&data) != 0) {
      /// 如果找不到空闲的 frame，返回错误
      return -1;
    } else {
      /// 从 frames 中获取一个空闲的帧号
      frame_number = *data;
      free(data);
    }
  }
  return frame_number;
}


int free_frame(List *frames, int frame_number)
{
  int *data;
  
  /// 获取存储页帧号的空间
  if ((data = (int *) malloc(sizeof(int))) == NULL) {
    return -1;
  }
  
  /// 将对应的页帧放回帧链表
  *data = frame_number;
  if (list_ins_next(frames, NULL, data) != 0) {
    return -1;
  }
  
  return 0;
}
