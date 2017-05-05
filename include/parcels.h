//
//  parcels.h
//  Algorithms - Parcels
//
//  Created by YourtionGuo on 05/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#ifndef PARCELS_H
#define PARCELS_H

#include "parcel.h"
#include "pqueue.h"


/**
 在优先队列 parcels 获取下一个包裹

 @param parcels 包裹优先队列
 @param parcel 包裹
 @return 成功返回0；否则返回-1
 */
int get_parcel(PQueue *parcels, Parcel *parcel);


/**
 将一个包裹 parcel 插入一个优先队列 parcels

 @param parcels 包裹优先队列
 @param parcel 包裹
 @return 成功，返回0；否则返回-1
 */
int put_parcel(PQueue *parcels, const Parcel *parcel);

#endif /* PARCELS_H */
