//
//  main.c
//  MasteringAlgorithms
//  Description: Illustrates sorting algorithms (see Chapter 12).
//
//  Created by YourtionGuo on 10/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <stdio.h>
#include <string.h>

#include "sort.h"

/// 定义字符串长度
#define     STRSIZ      6


static void print_idata(const int *array, int size)
{
  int       i;

  /// 打印整数数组
  fprintf(stdout, "-> Int Array size: %d \n--> [ ", size);
  for (i = 0; i < size; i++) {
    fprintf(stdout, "%d ", array[i]);
  }
  fprintf(stdout, "]\n");

  return;
}


static void print_sdata(char array[][STRSIZ], int size)
{
  int       i;
  
  /// 打印整数数组
  fprintf(stdout, "-> String Array size: %d \n--> [ ", size);
  for (i = 0; i < size; i++) {
    fprintf(stdout, "%s ", array[i]);
  }
  fprintf(stdout, "]\n");

  return;
}


static int compare_int(const void *int1, const void *int2)
{
  /// 比较整数
  if (*(const int *)int1 > *(const int *)int2) return 1;
  if (*(const int *)int1 < *(const int *)int2) return -1;
  return 0;
}

static int compare_str(const void *str1, const void *str2)
{
  int       retval;

  /// 比较两个字符
  if ((retval = strcmp((const char *)str1, (const char *)str2)) > 0) return 1;
  if (retval < 0) return -1;
  return 0;
}


int main(int argc, char **argv)
{

  int       iarray[10], marray[10], qarray[10], carray[10], rarray[10], qarray2[10];
  char      sarray[10][STRSIZ], sarray2[10][STRSIZ];
  int       size = 10;

  /// 加载用于排序的数据

  iarray[0] = 0;
  iarray[1] = 5;
  iarray[2] = 1;
  iarray[3] = 7;
  iarray[4] = 3;
  iarray[5] = 2;
  iarray[6] = 8;
  iarray[7] = 9;
  iarray[8] = 4;
  iarray[9] = 6;

  memcpy(marray, iarray, size * sizeof(int));
  memcpy(qarray, iarray, size * sizeof(int));
  memcpy(qarray2, iarray, size * sizeof(int));
  memcpy(carray, iarray, size * sizeof(int));

  rarray[0] = 11111323;
  rarray[1] = 99283743;
  rarray[2] = 98298383;
  rarray[3] = 99987444;
  rarray[4] = 43985209;
  rarray[5] = 99911110;
  rarray[6] = 11111324;
  rarray[7] = 39842329;
  rarray[8] = 97211029;
  rarray[9] = 99272928;

  strcpy(sarray[0], "ebcde");
  strcpy(sarray[1], "ghidj");
  strcpy(sarray[2], "ghiea");
  strcpy(sarray[3], "abaae");
  strcpy(sarray[4], "abaaa");
  strcpy(sarray[5], "abcde");
  strcpy(sarray[6], "abbcd");
  strcpy(sarray[7], "ddaab");
  strcpy(sarray[8], "faeja");
  strcpy(sarray[9], "aaaaa");

  memcpy(sarray2, sarray, size * STRSIZ * sizeof(char));

  /// 执行插入排序

  fprintf(stdout, "Before issort\n");
  print_idata(iarray, size);

  if (issort(iarray, size, sizeof(int), compare_int) != 0) return 1;

  fprintf(stdout, "After issort\n");
  print_idata(iarray, size);

  /// 执行快速排序
  fprintf(stdout, "\n");

  fprintf(stdout, "Before qksort\n");
  print_idata(qarray, size);

  if (qksort(qarray, size, sizeof(int), 0, size - 1, compare_int) != 0) return 1;

  fprintf(stdout, "After qksort\n");
  print_idata(qarray, size);

  /// 执行归并排序
  fprintf(stdout, "\n");

  fprintf(stdout, "Before mgsort\n");
  print_sdata(sarray, size);

  if (mgsort(sarray, size, STRSIZ, 0, size - 1, compare_str) != 0) return 1;

  fprintf(stdout, "After mgsort\n");
  print_sdata(sarray, size);

  /// 执行计数排序
  fprintf(stdout, "\n");

  fprintf(stdout, "Before ctsort\n");
  print_idata(carray, size);

  if (ctsort(carray, size, 10) != 0) return 1;

  fprintf(stdout, "After ctsort\n");
  print_idata(carray, size);

  /// 执行基数排序
  fprintf(stdout, "\n");

  fprintf(stdout, "Before rxsort\n");
  print_idata(rarray, size);

  if (rxsort(rarray, size, 8, 10) != 0) return 1;

  fprintf(stdout, "After rxsort\n");
  print_idata(rarray, size);

  /// 执行快速排序简化
  fprintf(stdout, "\n");

  fprintf(stdout, "Before qsrt\n");
  print_idata(qarray2, size);

  if (qsrt(qarray2, size, sizeof(int), compare_int) != 0) return 1;

  fprintf(stdout, "After qsrt\n");
  print_idata(qarray2, size);

  /// 执行归并排序简化
  fprintf(stdout, "\n");

  fprintf(stdout, "Before mgsrt\n");
  print_sdata(sarray2, size);

  if (mgsrt(sarray2, size, STRSIZ, compare_str) != 0) return 1;

  fprintf(stdout, "After mgsrt\n");
  print_sdata(sarray2, size);

  return 0;
}
