//
//  main.c
//  MasteringAlgorithms
//  Illustrates geometric algorithms (see Chapter 17).
//
//  Created by YourtionGuo on 25/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <math.h>
#include <stdio.h>

#include "geometry.h"
#include "list.h"

/// 定义凸包检测数据
#define     CVXPCT      10

static Point CvxTestP[CVXPCT] =
{
  { 0.0,  1.0, 0.0},
  {-3.0,  5.0, 0.0},
  {-2.0, -3.0, 0.0},
  { 0.0,  0.0, 0.0},
  { 3.0,  2.0, 0.0},
  {-5.0, -2.0, 0.0},
  { 5.0,  3.0, 0.0},
  {-3.0,  3.0, 0.0},
  { 2.0,  3.0, 0.0},
  {-3.0, -1.0, 0.0}
};


int main(int argc, char **argv)
{

  List      P, polygon;
  ListElmt  *element;
  Point     p1_rct, p2_rct, p3_rct, p4_rct, *point;
  SPoint    p1_sph, p2_sph;
  double    length;
  int       actual, i;

  /// 判断两条直线是否相交

  fprintf(stdout, "Determining whether two line segments intersect\n");

  p1_rct.x = 2.0;
  p1_rct.y = -1.0;
  p1_rct.z = 0.0;

  p2_rct.x = 4.0;
  p2_rct.y = -1.0;
  p2_rct.z = 0.0;

  p3_rct.x = 1.0;
  p3_rct.y = -2.0;
  p3_rct.z = 0.0;

  p4_rct.x = 3.0;
  p4_rct.y = 2.0;
  p4_rct.z = 0.0;

  if (lint(p1_rct, p2_rct, p3_rct, p4_rct)) {

    fprintf(stdout, "(%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) and (%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) Y",
            p1_rct.x, p1_rct.y, p2_rct.x, p2_rct.y, p3_rct.x, p3_rct.y, p4_rct.x, p4_rct.y);

  } else {

    fprintf(stdout, "(%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) and (%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) N",
            p1_rct.x, p1_rct.y, p2_rct.x, p2_rct.y, p3_rct.x, p3_rct.y, p4_rct.x, p4_rct.y);

  }

  fprintf(stdout, " (N=OK)\n");

  p1_rct.x = -4.0;
  p1_rct.y = -3.0;
  p1_rct.z = 0.0;

  p2_rct.x = -2.0;
  p2_rct.y = -1.0;
  p2_rct.z = 0.0;

  p3_rct.x = -1.0;
  p3_rct.y = 0.0;
  p3_rct.z = 0.0;

  p4_rct.x = 1.0;
  p4_rct.y = 2.0;
  p4_rct.z = 0.0;

  if (lint(p1_rct, p2_rct, p3_rct, p4_rct)) {

    fprintf(stdout, "(%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) and (%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) Y",
            p1_rct.x, p1_rct.y, p2_rct.x, p2_rct.y, p3_rct.x, p3_rct.y, p4_rct.x, p4_rct.y);

  } else {

    fprintf(stdout, "(%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) and (%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) N",
            p1_rct.x, p1_rct.y, p2_rct.x, p2_rct.y, p3_rct.x, p3_rct.y, p4_rct.x, p4_rct.y);

  }

  fprintf(stdout, " (N=OK)\n");

  p1_rct.x = -4.0;
  p1_rct.y = -3.0;
  p1_rct.z = 0.0;

  p2_rct.x = -2.0;
  p2_rct.y = -1.0;
  p2_rct.z = 0.0;

  p3_rct.x = -4.0;
  p3_rct.y = -1.0;
  p3_rct.z = 0.0;

  p4_rct.x = -3.0;
  p4_rct.y = -2.0;
  p4_rct.z = 0.0;

  if (lint(p1_rct, p2_rct, p3_rct, p4_rct)) {

    fprintf(stdout, "(%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) and (%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) Y",
            p1_rct.x, p1_rct.y, p2_rct.x, p2_rct.y, p3_rct.x, p3_rct.y, p4_rct.x, p4_rct.y);

  } else {

    fprintf(stdout, "(%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) and (%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) N",
            p1_rct.x, p1_rct.y, p2_rct.x, p2_rct.y, p3_rct.x, p3_rct.y, p4_rct.x, p4_rct.y);

  }

  fprintf(stdout, " (Y=OK)\n");

  p1_rct.x = -4.0;
  p1_rct.y = -3.0;
  p1_rct.z = 0.0;

  p2_rct.x = -2.0;
  p2_rct.y = -1.0;
  p2_rct.z = 0.0;

  p3_rct.x = -3.0;
  p3_rct.y = -2.0;
  p3_rct.z = 0.0;

  p4_rct.x = -3.0;
  p4_rct.y = -2.0;
  p4_rct.z = 0.0;

  if (lint(p1_rct, p2_rct, p3_rct, p4_rct)) {

    fprintf(stdout, "(%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) and (%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) Y",
            p1_rct.x, p1_rct.y, p2_rct.x, p2_rct.y, p3_rct.x, p3_rct.y, p4_rct.x, p4_rct.y);

  } else {

    fprintf(stdout, "(%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) and (%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) N",
            p1_rct.x, p1_rct.y, p2_rct.x, p2_rct.y, p3_rct.x, p3_rct.y, p4_rct.x, p4_rct.y);

  }

  fprintf(stdout, " (Y=OK)\n");

  p1_rct.x = -3.0;
  p1_rct.y = -2.0;
  p1_rct.z = 0.0;

  p2_rct.x = -3.0;
  p2_rct.y = -2.0;
  p2_rct.z = 0.0;

  p3_rct.x = -3.0;
  p3_rct.y = -2.0;
  p3_rct.z = 0.0;

  p4_rct.x = -3.0;
  p4_rct.y = -2.0;
  p4_rct.z = 0.0;

  if (lint(p1_rct, p2_rct, p3_rct, p4_rct)) {

    fprintf(stdout, "(%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) and (%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) Y",
            p1_rct.x, p1_rct.y, p2_rct.x, p2_rct.y, p3_rct.x, p3_rct.y, p4_rct.x, p4_rct.y);

  } else {

    fprintf(stdout, "(%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) and (%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) N",
            p1_rct.x, p1_rct.y, p2_rct.x, p2_rct.y, p3_rct.x, p3_rct.y, p4_rct.x, p4_rct.y);

  }

  fprintf(stdout, " (Y=OK)\n");

  p1_rct.x = -3.0;
  p1_rct.y = -2.0;
  p1_rct.z = 0.0;

  p2_rct.x = 3.0;
  p2_rct.y = 4.0;
  p2_rct.z = 0.0;

  p3_rct.x = -1.0;
  p3_rct.y = 2.0;
  p3_rct.z = 0.0;

  p4_rct.x = 3.0;
  p4_rct.y = -1.0;
  p4_rct.z = 0.0;

  if (lint(p1_rct, p2_rct, p3_rct, p4_rct)) {

    fprintf(stdout, "(%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) and (%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) Y",
            p1_rct.x, p1_rct.y, p2_rct.x, p2_rct.y, p3_rct.x, p3_rct.y, p4_rct.x, p4_rct.y);

  } else {

    fprintf(stdout, "(%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) and (%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) N",
            p1_rct.x, p1_rct.y, p2_rct.x, p2_rct.y, p3_rct.x, p3_rct.y, p4_rct.x, p4_rct.y);

  }

  fprintf(stdout, " (Y=OK)\n");

  p1_rct.x = -3.0;
  p1_rct.y = -2.0;
  p1_rct.z = 0.0;

  p2_rct.x = 3.0;
  p2_rct.y = 4.0;
  p2_rct.z = 0.0;

  p3_rct.x = -1.0;
  p3_rct.y = -2.0;
  p3_rct.z = 0.0;

  p4_rct.x = 3.0;
  p4_rct.y = 1.0;
  p4_rct.z = 0.0;

  if (lint(p1_rct, p2_rct, p3_rct, p4_rct)) {

    fprintf(stdout, "(%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) and (%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) Y",
            p1_rct.x, p1_rct.y, p2_rct.x, p2_rct.y, p3_rct.x, p3_rct.y, p4_rct.x, p4_rct.y);

  } else {

    fprintf(stdout, "(%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) and (%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) N",
            p1_rct.x, p1_rct.y, p2_rct.x, p2_rct.y, p3_rct.x, p3_rct.y, p4_rct.x, p4_rct.y);

  }

  fprintf(stdout, " (N=OK)\n");

  p1_rct.x = -3.0;
  p1_rct.y = -2.0;
  p1_rct.z = 0.0;

  p2_rct.x = 3.0;
  p2_rct.y = 4.0;
  p2_rct.z = 0.0;

  p3_rct.x = -3.0;
  p3_rct.y = -2.0;
  p3_rct.z = 0.0;

  p4_rct.x = -4.0;
  p4_rct.y = 3.0;
  p4_rct.z = 0.0;

  if (lint(p1_rct, p2_rct, p3_rct, p4_rct)) {

    fprintf(stdout, "(%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) and (%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) Y",
            p1_rct.x, p1_rct.y, p2_rct.x, p2_rct.y, p3_rct.x, p3_rct.y, p4_rct.x, p4_rct.y);

  } else {

    fprintf(stdout, "(%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) and (%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) N",
            p1_rct.x, p1_rct.y, p2_rct.x, p2_rct.y, p3_rct.x, p3_rct.y, p4_rct.x, p4_rct.y);

  }

  fprintf(stdout, " (Y=OK)\n");

  p1_rct.x = -3.0;
  p1_rct.y = -1.0;
  p1_rct.z = 0.0;

  p2_rct.x = 3.0;
  p2_rct.y = 4.0;
  p2_rct.z = 0.0;

  p3_rct.x = -3.0;
  p3_rct.y = -2.0;
  p3_rct.z = 0.0;

  p4_rct.x = -4.0;
  p4_rct.y = 3.0;
  p4_rct.z = 0.0;

  if (lint(p1_rct, p2_rct, p3_rct, p4_rct)) {

    fprintf(stdout, "(%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) and (%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) Y",
            p1_rct.x, p1_rct.y, p2_rct.x, p2_rct.y, p3_rct.x, p3_rct.y, p4_rct.x, p4_rct.y);

  } else {

    fprintf(stdout, "(%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) and (%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) N",
            p1_rct.x, p1_rct.y, p2_rct.x, p2_rct.y, p3_rct.x, p3_rct.y, p4_rct.x, p4_rct.y);

  }

  fprintf(stdout, " (N=OK)\n");

  p1_rct.x = -3.0;
  p1_rct.y = -2.0;
  p1_rct.z = 0.0;

  p2_rct.x = 3.0;
  p2_rct.y = 4.0;
  p2_rct.z = 0.0;

  p3_rct.x = -3.0;
  p3_rct.y = -1.0;
  p3_rct.z = 0.0;

  p4_rct.x = -4.0;
  p4_rct.y = 3.0;
  p4_rct.z = 0.0;

  if (lint(p1_rct, p2_rct, p3_rct, p4_rct)) {

    fprintf(stdout, "(%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) and (%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) Y",
            p1_rct.x, p1_rct.y, p2_rct.x, p2_rct.y, p3_rct.x, p3_rct.y, p4_rct.x, p4_rct.y);

  } else {

    fprintf(stdout, "(%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) and (%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) N",
            p1_rct.x, p1_rct.y, p2_rct.x, p2_rct.y, p3_rct.x, p3_rct.y, p4_rct.x, p4_rct.y);

  }

  fprintf(stdout, " (N=OK)\n");

  p1_rct.x = -3.0;
  p1_rct.y = 0.0;
  p1_rct.z = 0.0;

  p2_rct.x = -4.0;
  p2_rct.y = 3.0;
  p2_rct.z = 0.0;

  p3_rct.x = -5.0;
  p3_rct.y = 6.0;
  p3_rct.z = 0.0;

  p4_rct.x = -6.0;
  p4_rct.y = 9.0;
  p4_rct.z = 0.0;

  if (lint(p1_rct, p2_rct, p3_rct, p4_rct)) {

    fprintf(stdout, "(%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) and (%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) Y",
            p1_rct.x, p1_rct.y, p2_rct.x, p2_rct.y, p3_rct.x, p3_rct.y, p4_rct.x, p4_rct.y);

  } else {

    fprintf(stdout, "(%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) and (%+.1lf,%+.1lf) to (%+.1lf,%+.1lf) N",
            p1_rct.x, p1_rct.y, p2_rct.x, p2_rct.y, p3_rct.x, p3_rct.y, p4_rct.x, p4_rct.y);

  }

  fprintf(stdout, " (N=OK)\n");

  /// 执行凸包检测

  fprintf(stdout, "Computing a convex hull\n");
  fprintf(stdout, "Points in P\n");

  list_init(&P, NULL);

  for (i = 0; i < CVXPCT; i++) {

    if (list_ins_next(&P, list_tail(&P), &CvxTestP[i]) != 0) {

      list_destroy(&P);
      return 1;
    }

    fprintf(stdout, "-> P[%03d]=(%+.1lf,%+.1lf,%+.1lf)\n", i, CvxTestP[i].x, CvxTestP[i].y, CvxTestP[i].z);
  }

  if (cvxhull(&P, &polygon) != 0) {

    list_destroy(&P);
    return 1;
  }

  fprintf(stdout, "Points in the convex hull\n");

  i = 0;

  for (element = list_head(&polygon); element != NULL; element = list_next(element)) {

    i++;
    point = list_data(element);

    fprintf(stdout, "-> polygon[%03d]=(%+.1lf,%+.1lf,%+.1lf)\n", i, point->x, point->y, point->z);
  }
  
  list_destroy(&P);
  list_destroy(&polygon);

  return 0;
}
