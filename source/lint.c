//
//  lint.c
//  Algorithms - Two line segments intersect
//
//  Created by YourtionGuo on 25/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include "geometry.h"

#pragma mark - Public


int lint(Point p1, Point p2, Point p3, Point p4)
{
  double    z1, z2, z3, z4;
  int       s1, s2, s3, s4;

  /// 执行快速剔除检测
  if (!(MAX(p1.x, p2.x) >= MIN(p3.x, p4.x)
        && MAX(p3.x, p4.x) >= MIN(p1.x, p2.x)
        && MAX(p1.y, p2.y) >= MIN(p3.y, p4.y)
        && MAX(p3.y, p4.y) >= MIN(p1.y, p2.y))) {

    return 0;
  }

  /*****************************************************************************
   *                                                                            *
   *  Determine whether the line segments straddle each other.                  *
   *                                                                            *
   *****************************************************************************/

  if ((z1 = ((p3.x - p1.x)*(p2.y - p1.y)) - ((p3.y - p1.y)*(p2.x - p1.x))) < 0) {
    s1 = -1;
  } else if (z1 > 0) {
    s1 = 1;
  } else {
    s1 = 0;
  }

  if ((z2 = ((p4.x - p1.x)*(p2.y - p1.y)) - ((p4.y - p1.y)*(p2.x - p1.x))) < 0) {
    s2 = -1;
  } else if (z2 > 0) {
    s2 = 1;
  } else {
    s2 = 0;
  }

  if ((z3 = ((p1.x - p3.x)*(p4.y - p3.y)) - ((p1.y - p3.y)*(p4.x - p3.x))) < 0) {
    s3 = -1;
  } else if (z3 > 0) {
    s3 = 1;
  } else {
    s3 = 0;
  }

  if ((z4 = ((p2.x - p3.x)*(p4.y - p3.y)) - ((p2.y - p3.y)*(p4.x - p3.x))) < 0) {
    s4 = -1;
  } else if (z4 > 0) {
    s4 = 1;
  } else {
    s4 = 0;
  }

  if ((s1 * s2 <= 0) && (s3 * s4 <= 0)) return 1;

  /// 如果线段没有相交返回 0
  return 0;
}
