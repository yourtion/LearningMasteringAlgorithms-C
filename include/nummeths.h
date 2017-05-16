//
//  nummeths.h
//  Algorithms - Number methods
//
//  Created by YourtionGuo on 16/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#ifndef NUMMETHS_H
#define NUMMETHS_H


/**
 采用多项式插值法来求得函数在某些特定点上的值 - O(mn2) m代表待求值的个数，n代表已知点的个数

 @param x 指定函数值已知的点集
 @param fx 每个已知点所对应的函数值
 @param n x 和 fx 中的元素个数
 @param z 待求的点
 @param pz 待求点返回值
 @param m 待求点的个数
 @return 插值成功返回0；否则返回-1
 */
int interpol(const double *x, const double *fx, int n, double *z, double *pz, int m);

void lsqe(const double *x, const double *y, int n, double *b1, double *b0);

int root(double (*f)(double x), double (*g)(double x), double *x, int *n, double delta);

#endif /* NUMMETHS_H */
