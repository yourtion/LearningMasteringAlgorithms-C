//
//  list.c
//  Algorithms - linked list
//
//  Created by YourtionGuo on 05/04/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <stdio.h>
#include <string.h>

#include "list.h"

#pragma mark - Public


void list_init(List *list, void (*destroy)(void *data))
{
  /// 初始化链表
  list->size = 0;
  list->destroy = destroy;
  list->head = NULL;
  list->tail = NULL;
  
  return;
}


void list_destroy(List *list)
{
  void *data;
  
  /// 删除每一个元素
  while (list_size(list) > 0) {
    if (list_rem_next(list, NULL, (void **)&data) == 0 && list->destroy != NULL) {
      /// 调用用户定义的 destroy 方法销毁动态创建的数据
      list->destroy(data);
    }
  }

  /// 清理链表结构体数据
  memset(list, 0, sizeof(List));
  
  return;
}


int list_ins_next(List *list, ListElmt *element, const void *data)
{
  ListElmt *new_element;
  
  /// 分配元素需要的空间
  if ((new_element = (ListElmt *)malloc(sizeof(ListElmt))) == NULL) return -1;
  
  /// 插入元素到链表
  new_element->data = (void *)data;
  
  if (element == NULL) {
    
    /// 处理插入到头部的情况
    
    if (list_size(list) == 0) {
      list->tail = new_element;
    }
    
    new_element->next = list->head;
    list->head = new_element;
    
  } else {
    
    /// 处理其他情况
    
    if (element->next == NULL) {
      list->tail = new_element;
    }
    
    new_element->next = element->next;
    element->next = new_element;
    
  }
  
  /// 更新链表的 size
  list->size++;
  
  return 0;
}


int list_rem_next(List *list, ListElmt *element, void **data)
{  
  ListElmt *old_element;
  
  /// 禁止删除空链表的数据
  if (list_size(list) == 0) return -1;
  
  /// 从链表中删除元素
  if (element == NULL) {
    
    /// 处理删除头部元素
    
    *data = list->head->data;
    old_element = list->head;
    list->head = list->head->next;
    
    if (list_size(list) == 1) {
      list->tail = NULL;
    }
    
  } else {
    
    /// 处理其他情况
    
    if (element->next == NULL) return -1;
    
    *data = element->next->data;
    old_element = element->next;
    element->next = element->next->next;
    
    if (element->next == NULL) {
      list->tail = element;
    }
    
  }
  
  /// 清理旧结点元素的
  free(old_element);
  
  /// 更新链表的 size
  list->size--;
  
  return 0;
}
