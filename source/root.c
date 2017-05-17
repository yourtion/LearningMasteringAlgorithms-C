//
//  root.c
//  Algorithms - Find the roots
//
//  Created by YourtionGuo on 16/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <math.h>

#include "nummeths.h"

#pragma mark - Public


int root(double (*f)(double x), double (*g)(double x), double *x, int *n, double delta)
{
  int       satisfied, i;

  /// 使用牛顿迭代法找方程的根

  i = 0;
  satisfied = 0;

  while (!satisfied && i + 1 < *n) {

    /// 确定下一个迭代的 x
    x[i + 1] = x[i] - (f(x[i]) / g(x[i]));

    /// 确定是否找到想要的近似值
    if (fabs(x[i + 1] - x[i]) < delta) {
      satisfied = 1;
    }

    /// 准备下一次迭代
    i++;
  }

  /// 即使没有迭代，表明一个值已被存入 x

  if (i == 0) {
    *n = 1;
  } else {
    *n = i + 1;
  }

  /// 返回找到根或者到达最大迭代次数
  
  if (satisfied) return 0;
  return -1;
}
