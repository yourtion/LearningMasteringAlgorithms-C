//
//  main.c
//  MasteringAlgorithms
//  Illustrates using a circular list (see Chapter 5).
//
//  Created by YourtionGuo on 24/04/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "clist.h"


static void print_list(const CList *list)
{
  CListElmt   *element;
  int         *data, size, i;
  
  /// 显示链表
  fprintf(stdout, "-> CList size is %d (circling twice)\n", clist_size(list));
  
  size = clist_size(list);
  element = clist_head(list);
  
  /// 循环两次验证循环链表
  i = 0;
  
  while (i < size * 2) {
    
    data = clist_data(element);
    fprintf(stdout, "--> list[%03d]=%03d\n", (i % size), *data);
    element = clist_next(element);
    i++;
    
  }
  
  return;
}


int main(int argc, char **argv)
{
  CList              list;
  CListElmt          *element;
  int                *data, i;
  
  /// 初始化链表
  clist_init(&list, free);
  
  /// 执行链表操作
  element = clist_head(&list);
  
  for (i = 0; i < 10; i++) {
    
    if ((data = (int *)malloc(sizeof(int))) == NULL) return 1;
    
    *data = i + 1;
    
    if (clist_ins_next(&list, element, data) != 0) return 1;
    
    if (element == NULL) {
      element = clist_next(clist_head(&list));
    } else {
      element = clist_next(element);
    }
  }
  
  print_list(&list);
  
  element = clist_head(&list);
  
  for (i = 0; i < 10; i++) {
    element = clist_next(element);
  }
  
  data = clist_data(element);
  fprintf(stdout, "Circling and removing an element after the one containing %03d\n",*data);
  
  if (clist_rem_next(&list, element, (void **)&data) != 0) return 1;
  
  free(data);
  print_list(&list);
  
  element = clist_head(&list);
  
  for (i = 0; i < 15; i++) {
    element = clist_next(element);
  }
  
  data = clist_data(element);
  fprintf(stdout, "Circling and inserting 011 after the element containing %03d\n", *data);
  
  if ((data = (int *)malloc(sizeof(int))) == NULL) return 1;
  
  *data = 11;
  if (clist_ins_next(&list, element, data) != 0) return 1;
  
  print_list(&list);
  
  /// 销毁链表
  fprintf(stdout, "Destroying the list\n");
  clist_destroy(&list);
  
  return 0;
}
