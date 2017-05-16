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

  return 0;
}
