//
//  geometry.h
//  Algorithms - Geometry
//
//  Created by YourtionGuo on 25/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "list.h"

/// 定义 PI
#ifndef PI
#define     PI      3.14159
#endif

/// 定义大小比较宏
#define     MIN(x, y)     (((x) < (y)) ? (x) : (y))
#define     MAX(x, y)     (((x) > (y)) ? (x) : (y))

/// 计算角度与弧度转换宏
#define     DEGTORAD(deg)     (((deg) * 2.0 * PI) / 360.0)
#define     RADTODEG(rad)     (((rad) * 360.0) / (2.0 * PI))

/**
 直角坐标系中的点
 */
typedef struct Point_
{
  double      x, y, z;

} Point;


/**
 球坐标系中的点
 */
typedef struct SPoint_
{
  double      rho, theta, phi;

} SPoint;


/**
 检测两条线段是否相交 - O(1)

 @param p1 线段 1 起点
 @param p2 线段 1 终点
 @param p3 线段 2 起点
 @param p4 线段 2 终点
 @return 两条线段相交返回1；否则返回0
 */
int lint(Point p1, Point p2, Point p3, Point p4);

int cvxhull(const List *P, List *polygon);

void arclen(SPoint p1, SPoint p2, double *length);

#endif /* GEOMETRY_H */
