//
//  clist.c
//  Algorithms - circular list 
//
//  Created by YourtionGuo on 24/04/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <stdlib.h>
#include <string.h>

#include "clist.h"

#pragma mark - Public


void clist_init(CList *list, void (*destroy)(void *data))
{
  /// 初始化链表
  list->size = 0;
  list->destroy = destroy;
  list->head = NULL;
  
  return;
}


void clist_destroy(CList *list)
{
  void *data;
  
  /// 删除每一个元素
  while (clist_size(list) > 0) {
    if (clist_rem_next(list, list->head, (void **)&data) == 0 && list->destroy != NULL) {
      /// 调用用户定义的 destroy 方法销毁动态创建的数据
      list->destroy(data);
    }
  }
  
  /// 清理链表结构体数据
  memset(list, 0, sizeof(CList));
  
  return;
}


int clist_ins_next(CList *list, CListElmt *element, const void *data)
{
  CListElmt *new_element;
  
  /// 分配元素需要的空间
  if ((new_element = (CListElmt *)malloc(sizeof(CListElmt))) == NULL) return -1;
  
  /// 插入元素到链表
  new_element->data = (void *)data;
  
  if (clist_size(list) == 0) {
    
    /// 处理插入空循环链表
    new_element->next = new_element;
    list->head = new_element;
    
  } else {
    
    /// 处理非空情况
    new_element->next = element->next;
    element->next = new_element;
    
  }
  
  /// 更新链表的 size
  list->size++;
  
  return 0;
}


int clist_rem_next(CList *list, CListElmt *element, void **data)
{
  CListElmt *old_element;
  
  /// 禁止删除空链表的数据
  if (clist_size(list) == 0) return -1;
  
  /// 从链表中删除元素
  *data = element->next->data;
  if (element->next == element) {
    
    /// 处理删除最后一个元素
    old_element = element->next;
    list->head = NULL;
    
  } else {
    
    /// 处理其他情况
    old_element = element->next;
    element->next = element->next->next;
    
    if (old_element == clist_head(list)) {
      list->head = old_element->next;
    }
    
  }
  
  /// 清理旧结点元素的
  free(old_element);
  
  /// 更新链表的 size
  list->size--;
  
  return 0;
}
