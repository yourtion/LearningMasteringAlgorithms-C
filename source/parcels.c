//
//  parcels.c
//  Algorithms - Parcels
//
//  Created by YourtionGuo on 05/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <stdlib.h>
#include <string.h>

#include "parcel.h"
#include "parcels.h"
#include "pqueue.h"


int get_parcel(PQueue *parcels, Parcel *parcel)
{
  Parcel      *data;

  /// 如果没有包裹返回 -1
  if (pqueue_size(parcels) == 0) return -1;

  /// 无法获取包裹返回 -1
  if (pqueue_extract(parcels, (void **)&data) != 0) return -1;

  memcpy(parcel, data, sizeof(Parcel));
  free(data);

  return 0;
}


int put_parcel(PQueue *parcels, const Parcel *parcel)
{
  Parcel      *data;

  /// 初始化包裹内存空间
  if ((data = (Parcel *)malloc(sizeof(Parcel))) == NULL) return -1;

  /// 将包裹插入到优先队列
  
  memcpy(data, parcel, sizeof(Parcel));
  
  if (pqueue_insert(parcels, data) != 0) return -1;
  
  return 0;
}
