//
//  main.c
//  MasteringAlgorithms
//  Illustrates numerical methods (see Chapter 13).
//
//  Created by YourtionGuo on 16/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <math.h>
#include <stdio.h>

#include "nummeths.h"

/// 数组最大 size
#define     SIZE      50

static double f(double x)
{
  return (pow(x, 3.0)) - (pow(x, 2.0)) - (3.0 * x) + 1.8;
}


static double g(double x)
{
  return (3.0 * pow(x, 2.0)) - (2.0 * x) - 3.0;
}

int main(int argc, char **argv)
{
  double    x[SIZE], fx[SIZE], z[SIZE], pz[SIZE], y[SIZE], b1, b0;
  int       retval, i, n;

  /// 插值多项式计算

  fprintf(stdout, "Perform polynomial interpolation\n");

  x[0] = -3.0; fx[0] = -5.0;
  x[1] = -2.0; fx[1] = -1.1;
  x[2] =  2.0; fx[2] =  1.9;
  x[3] =  3.0; fx[3] =  4.8;

  z[0] = -2.5;
  z[1] = -1.0;
  z[2] =  0.0;
  z[3] =  1.0;
  z[4] =  1.5;
  z[5] =  2.5;

  if (interpol(x, fx, 4, z, pz, 6) != 0) return 1;

  fprintf(stdout, "Interpolating f(z) with p(z)\n");

  for (i = 0; i < 4; i++) {
    fprintf(stdout, "-> x[%d]=%+1.6e, f(x[%d])=%+1.6e\n", i, x[i], i, fx[i]);
  }

  for (i = 0; i < 6; i++) {
    fprintf(stdout, "-> z[%d]=%+1.6e, p(z[%d])=%+1.6e\n", i, z[i], i, pz[i]);
  }

  x[0] = -4.0; fx[0] = -3.0;
  x[1] = -3.5; fx[1] =  1.5;
  x[2] = -2.5; fx[2] =  2.5;
  x[3] = -1.5; fx[3] =  1.5;
  x[4] =  0.0; fx[4] =  0.5;
  x[5] =  1.5; fx[5] =  1.5;
  x[6] =  2.5; fx[6] =  2.5;
  x[7] =  3.5; fx[7] =  1.5;
  x[8] =  4.0; fx[8] = -3.0;

  z[0] = -0.50;
  z[1] = -1.00;
  z[2] = -2.00;
  z[3] = -3.00;
  z[4] = -3.25;
  z[5] = -3.50;
  z[6] = -3.75;

  if (interpol(x, fx, 9, z, pz, 7) != 0) return 1;

  fprintf(stdout, "Interpolating f(z) with p(z)\n");

  for (i = 0; i < 9; i++) {
    fprintf(stdout, "-> x[%d]=%+1.6e, f(x[%d])=%+1.6e\n", i, x[i], i, fx[i]);
  }

  for (i = 0; i < 7; i++) {
    fprintf(stdout, "-> z[%d]=%+1.6e, p(z[%d])=%+1.6e\n", i, z[i], i, pz[i]);
  }


  /// 最小二乘估计法

  fprintf(stdout, "Perform least-squares estimation\n");

  x[0] =  4.0; y[0] =  197.0;
  x[1] =  6.0; y[1] =  272.0;
  x[2] =  2.0; y[2] =  100.0;
  x[3] =  5.0; y[3] =  228.0;
  x[4] =  7.0; y[4] =  327.0;
  x[5] =  6.0; y[5] =  279.0;
  x[6] =  3.0; y[6] =  148.0;
  x[7] =  8.0; y[7] =  377.0;
  x[8] =  5.0; y[8] =  238.0;
  x[9] =  3.0; y[9] =  142.0;
  x[10] = 1.0; y[10] =  66.0;
  x[11] = 5.0; y[11] = 239.0;

  for (i = 0; i < 12; i++) {
    fprintf(stdout, "-> x[%02d]=%+1.6e, y[%02d]=%+1.6e\n", i, x[i], i, y[i]);
  }

  lsqe(x, y, 12, &b1, &b0);

  fprintf(stdout, "-> b1=%+1.6e, b0=%+1.6e\n", b1, b0);


  /// 采用牛顿迭代法找方程的根

  fprintf(stdout, "Finding the roots of an equation\n");

  n = 10;
  x[0] = -2.0;
  retval = root(f, g, x, &n, 0.0001);

  for (i = 0; i < n; i++) {
    fprintf(stdout, "-> x[%d]=%+1.6e\n", i, x[i]);
  }

  if (retval != 0) {
    fprintf(stdout, "Did not find a root\n");
  } else {
    fprintf(stdout, "Found a root at %+1.6e\n", x[n - 1]);
  }

  n = 10;
  x[0] = 0.5;
  retval = root(f, g, x, &n, 0.0001);

  for (i = 0; i < n; i++) {
    fprintf(stdout, "-> x[%d]=%+1.6e\n", i, x[i]);
  }

  if (retval != 0) {
    fprintf(stdout, "Did not find a root\n");
  } else {
    fprintf(stdout, "Found a root at %+1.6e\n", x[n - 1]);
  }

  n = 10;
  x[0] = 2.0;
  retval = root(f, g, x, &n, 0.0001);

  for (i = 0; i < n; i++)
    fprintf(stdout, "x[%d]=%+1.6e\n", i, x[i]);

  if (retval != 0) {
    fprintf(stdout, "Did not find a root\n");
  } else {
    fprintf(stdout, "Found a root at %+1.6e\n", x[n - 1]);
  }

  return 0;
}
