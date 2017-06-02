//
//  dlist.c
//  Algorithms - doubly-linked list
//
//  Created by YourtionGuo on 24/04/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <stdio.h>
#include <string.h>

#include "dlist.h"

#pragma mark - Public


void dlist_init(DList *list, void (*destory)(void *data))
{
  /// 初始化链表
  list->size = 0;
  list->destroy = destory;
  list->head = NULL;
  list->tail = NULL;
  
  return;
}


void dlist_destroy(DList *list)
{
  void *data;
  
  /// 删除每一个元素
  while (dlist_size(list) > 0) {
    if (dlist_remove(list, dlist_tail(list), (void **)&data) == 0 && list->destroy != NULL) {
      /// 调用用户定义的 destroy 方法销毁动态创建的数据
      list->destroy(data);
    }
  }
  
  /// 清理链表结构体数据
  memset(list, 0, sizeof(DList));
  
  return;
}


int dlist_ins_next(DList *list, DListElmt *element, const void *data)
{
  DListElmt *new_element;
  
  /// 除非是空双向链表，否则不允许 element 为 NULL
  if (element == NULL && dlist_size(list) != 0) return -1;
  
  /// 分配元素需要的空间
  if ((new_element = (DListElmt *)malloc(sizeof(DListElmt))) == NULL) return -1;
  
  /// 插入元素到链表
  new_element->data = (void *)data;
  
  if (dlist_size(list) == 0) {
    /// 处理空双向链表
    
    list->head = new_element;
    list->head->prev = NULL;
    list->head->next = NULL;
    list->tail = new_element;
    
  } else {
    /// 处理非空双向链表
    
    new_element->next = element->next;
    new_element->prev = element;
    
    if (element->next == NULL) {
      list->tail = new_element;
    } else {
      element->next->prev = new_element;
    }
    
    element->next = new_element;
    
  }
  
  /// 更新链表的 size
  list->size++;
  
  return 0;
}


int dlist_ins_prev(DList *list, DListElmt *element, const void *data)
{
  DListElmt *new_element;
  
  /// 除非是空双向链表，否则不允许 element 为 NULL
  if (element == NULL && dlist_size(list) != 0) return -1;
  
  /// 分配元素需要的空间
  if ((new_element = (DListElmt *)malloc(sizeof(DListElmt))) == NULL) return -1;
  
  /// 插入元素到链表
  new_element->data = (void *)data;
  
  if (dlist_size(list) == 0) {
    /// 处理空双向链表
    
    list->head = new_element;
    list->head->prev = NULL;
    list->head->next = NULL;
    list->tail = new_element;
    
  } else {
    /// 处理非空双向链表
    
    new_element->next = element;
    new_element->prev = element->prev;
    
    if (element->prev == NULL) {
      list->head = new_element;
    } else {
      element->prev->next = new_element;
    }
    
    element->prev = new_element;
    
  }
  
  /// 更新链表的 size
  list->size++;
  
  return 0;
}


int dlist_remove(DList *list, DListElmt *element, void **data)
{
  /// 禁止删除 element 为空或空链表的数据
  if (element == NULL || dlist_size(list) == 0) return -1;

  *data = element->data;
  
  if (element == list->head) {
    
    /// 处理删除头部元素
    
    list->head = element->next;
    
    if (list->head == NULL) {
      list->tail = NULL;
    } else {
      element->next->prev = NULL;
    }
  } else {
    
    /// 处理删除非头部元素
    
    element->prev->next = element->next;
    
    if (element->next == NULL) {
      list->tail = element->prev;
    } else {
      element->next->prev = element->prev;
    }
  }
  
  /// 清理旧结点元素的
  free(element);
  
  /// 更新链表的 size
  list->size--;
  
  return 0;
}
