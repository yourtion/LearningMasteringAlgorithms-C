//
//  interpol.c
//  Algorithms - Interpolate
//
//  Created by YourtionGuo on 16/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <stdlib.h>
#include <string.h>

#include "nummeths.h"

#pragma mark - Public


int interpol(const double *x, const double *fx, int n, double *z, double *pz, int m)
{
  double    term, *table, *coeff;
  int       i, j, k;

  /// 为差商以及待确定的系数分配存储空间

  if ((table = (double *)malloc(sizeof(double) * n)) == NULL) return -1;

  if ((coeff = (double *)malloc(sizeof(double) * n)) == NULL) {

    free(table);
    return -1;
  }

  /// 初始化系数
  memcpy(table, fx, sizeof(double) * n);

  /// 确定插值多项式的系数

  coeff[0] = table[0];

  for (k = 1; k < n; k++) {

    for (i = 0; i < n - k; i++) {

      j = i + k;
      table[i] = (table[i + 1] - table[i]) / (x[j] - x[i]);
    }

    coeff[k] = table[0];
  }

  free(table);

  /// 计算插值多项式在特定点的值

  for (k = 0; k < m; k++) {

    pz[k] = coeff[0];

    for (j = 1; j < n; j++) {

      term = coeff[j];

      for (i = 0; i < j; i++) {
        term = term * (z[k] - x[i]);
      }

      pz[k] = pz[k] + term;
      
    }
  }
  
  free(coeff);
  
  return 0;
}

