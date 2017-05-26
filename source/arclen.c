//
//  arclen.c
//  Algorithms - Lengths on spherical surfaces
//
//  Created by YourtionGuo on 25/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <math.h>

#include "geometry.h"

#pragma mark - Public


void arclen(SPoint p1, SPoint p2, double *length)
{
  Point     p1_rct, p2_rct;
  double    alpha, dot;

  /// 将球面坐标系转换为直角坐标系
  p1_rct.x = p1.rho * sin(p1.phi) * cos(p1.theta);
  p1_rct.y = p1.rho * sin(p1.phi) * sin(p1.theta);
  p1_rct.z = p1.rho * cos(p1.phi);

  p2_rct.x = p2.rho * sin(p2.phi) * cos(p2.theta);
  p2_rct.y = p2.rho * sin(p2.phi) * sin(p2.theta);
  p2_rct.z = p2.rho * cos(p2.phi);


  /// 计算出从原点到点P1和P2这两条线段之间的夹角
  dot = (p1_rct.x * p2_rct.x) + (p1_rct.y * p2_rct.y) + (p1_rct.z * p2_rct.z);
  alpha = acos(dot / pow(p1.rho, 2.0));

  /// 通过计算该夹角与球体的半径之间的乘积来得到两点之间的弧长
  *length = alpha * p1.rho;
  
  return;
}
