//
//  lsqe.c
//  Algorithms
//
//  Created by YourtionGuo on 16/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//


#include <math.h>

#include "nummeths.h"

#pragma mark - Public


void lsqe(const double *x, const double *y, int n, double *b1, double *b0)
{
  double    sumx, sumy, sumx2, sumxy;
  int       i;

  /// 计算合计结果

  sumx = 0.0;
  sumy = 0.0;
  sumx2 = 0.0;
  sumxy = 0.0;

  for (i = 0; i < n; i++) {

    sumx = sumx + x[i];
    sumy = sumy + y[i];
    sumx2 = sumx2 + pow(x[i], 2.0);
    sumxy = sumxy + (x[i] * y[i]);

  }

  /// 计算最小二乘估计

  *b1 = (sumxy - ((sumx * sumy)/(double)n)) / (sumx2-(pow(sumx,2.0)/(double)n));
  *b0 = (sumy - ((*b1) * sumx)) / (double)n;
  
  return;
}
