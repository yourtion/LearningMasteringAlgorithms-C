//
//  main.c
//  MasteringAlgorithms
//  Illustrates using a heap (see Chapter 10).
//
//  Created by YourtionGuo on 05/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "heap.h"


static void print_heap(Heap *heap)
{
  int       i;

  /// 打印堆结构
  fprintf(stdout, "-> Heap size is %d\n", heap_size(heap));

  for (i = 0; i < heap_size(heap); i++) {
    fprintf(stdout, "--> Node=%03d\n", *(int *)heap->tree[i]);
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
  Heap      heap;
  void      *data;
  int       intval[30], i;

  /// 初始化堆
  heap_init(&heap, compare_int, NULL);

  /// 执行堆操作

  i = 0;

  intval[i] = 5;
  fprintf(stdout, "Inserting %03d\n", intval[i]);
  if (heap_insert(&heap, &intval[i]) != 0) return 1;
  print_heap(&heap);
  i++;

  intval[i] = 10;
  fprintf(stdout, "Inserting %03d\n", intval[i]);
  if (heap_insert(&heap, &intval[i]) != 0) return 1;
  print_heap(&heap);
  i++;

  intval[i] = 20;
  fprintf(stdout, "Inserting %03d\n", intval[i]);
  if (heap_insert(&heap, &intval[i]) != 0) return 1;
  print_heap(&heap);
  i++;

  intval[i] = 1;
  fprintf(stdout, "Inserting %03d\n", intval[i]);
  if (heap_insert(&heap, &intval[i]) != 0) return 1;
  print_heap(&heap);
  i++;

  intval[i] = 25;
  fprintf(stdout, "Inserting %03d\n", intval[i]);
  if (heap_insert(&heap, &intval[i]) != 0) return 1;
  print_heap(&heap);
  i++;

  intval[i] = 22;
  fprintf(stdout, "Inserting %03d\n", intval[i]);
  if (heap_insert(&heap, &intval[i]) != 0) return 1;
  print_heap(&heap);
  i++;

  intval[i] = 9;
  fprintf(stdout, "Inserting %03d\n", intval[i]);
  if (heap_insert(&heap, &intval[i]) != 0) return 1;
  print_heap(&heap);
  i++;

  while (heap_size(&heap) > 0) {

    if (heap_extract(&heap, (void **)&data) != 0) return 1;
    fprintf(stdout, "Extracting %03d\n", *(int *)data);
    print_heap(&heap);

  }

  /// 销毁堆
  
  fprintf(stdout, "Destroying the heap\n");
  heap_destroy(&heap);
  
  return 0;
}
