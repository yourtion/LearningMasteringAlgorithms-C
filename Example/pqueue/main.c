//
//  main.c
//  MasteringAlgorithms
//  Illustrates using a priority queue (see Chapter 10).
//
//  Created by YourtionGuo on 05/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "pqueue.h"


static void print_pqueue(PQueue *pqueue)
{
  int     i;

  /// 按顺序打印队列
  fprintf(stdout, "Priority queue size is %d\n", pqueue_size(pqueue));

  for (i = 0; i < pqueue_size(pqueue); i++) {
    fprintf(stdout, "Node=%03d\n", *(int *)pqueue->tree[i]);
  }

  return;
}


static int compare_int(const void *int1, const void *int2)
{
  /// 比较两个整数

  if (*(const int *)int1 > *(const int *)int2) return 1;

  if (*(const int *)int1 < *(const int *)int2) return -1;

  return 0;
}


int main(int argc, char **argv)
{

  PQueue    pqueue;
  void      *data;
  int       intval[30],
  i;

  /// 初始化优先队列
  pqueue_init(&pqueue, compare_int, NULL);

  /// 执行优先队列操作

  i = 0;

  intval[i] = 5;
  fprintf(stdout, "Inserting %03d\n", intval[i]);
  if (pqueue_insert(&pqueue, &intval[i]) != 0) return 1;
  print_pqueue(&pqueue);
  i++;

  intval[i] = 10;
  fprintf(stdout, "Inserting %03d\n", intval[i]);
  if (pqueue_insert(&pqueue, &intval[i]) != 0) return 1;
  print_pqueue(&pqueue);
  i++;

  intval[i] = 20;
  fprintf(stdout, "Inserting %03d\n", intval[i]);
  if (pqueue_insert(&pqueue, &intval[i]) != 0) return 1;
  print_pqueue(&pqueue);
  i++;

  intval[i] = 1;
  fprintf(stdout, "Inserting %03d\n", intval[i]);
  if (pqueue_insert(&pqueue, &intval[i]) != 0) return 1;
  print_pqueue(&pqueue);
  i++;

  intval[i] = 25;
  fprintf(stdout, "Inserting %03d\n", intval[i]);
  if (pqueue_insert(&pqueue, &intval[i]) != 0) return 1;
  print_pqueue(&pqueue);
  i++;

  intval[i] = 22;
  fprintf(stdout, "Inserting %03d\n", intval[i]);
  if (pqueue_insert(&pqueue, &intval[i]) != 0) return 1;
  print_pqueue(&pqueue);
  i++;

  intval[i] = 12;
  fprintf(stdout, "Inserting %03d\n", intval[i]);
  if (pqueue_insert(&pqueue, &intval[i]) != 0) return 1;
  print_pqueue(&pqueue);
  i++;

  while (pqueue_size(&pqueue) > 0) {

    fprintf(stdout, "Peeking at the highest priority element..Value=%03d\n", *(int *)pqueue_peek(&pqueue));
    if (pqueue_extract(&pqueue, (void **)&data) != 0) return 1;
    fprintf(stdout, "Extracting %03d\n", *(int *)data);
    print_pqueue(&pqueue);

  }

  /// 销毁优先队列
  fprintf(stdout, "Destroying the pqueue\n");
  pqueue_destroy(&pqueue);
  
  return 0;
}
