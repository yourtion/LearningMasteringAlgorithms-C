//
//  route.h
//  Algorithms - Route SPF
//
//  Created by YourtionGuo on 24/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#ifndef ROUTE_H
#define ROUTE_H

#include "graphalg.h"
#include "list.h"


/**
 计算路由下一个结点

 @param paths 路径信息列表（通过 shortest 计算）
 @param destination 目的地址
 @param next 指向下一结点顶点指针
 @param match 函数指针，用于判断两个成员是否相匹配（等于返回 1，否则返回 0）
 @return 计算成功返回0；否则，返回-1
 */
int route(List *paths, PathVertex *destination, PathVertex **next,
          int(*match)(const void *key1, const void *key2));

#endif /* ROUTE_H */
