//
//  dlist.h
//  Algorithms - doubly-linked list
//
//  Created by YourtionGuo on 24/04/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#ifndef DLIST_H
#define DLIST_H

#include <stdlib.h>

/**
 双向链表结点
 */
typedef struct DListElmt_
{
  void               *data;
  struct DListElmt_  *prev;
  struct DListElmt_  *next;
  
} DListElmt;


/**
 双向链表
 */
typedef struct DList_
{
  int         size;
  int         (*match)(const void *key1, const void *key2);
  void        (*destroy)(void *data);
  DListElmt   *head;
  DListElmt   *tail;
  
} DList;

/**
 初始化指定的双向链表 list - O(1)
 
 @param list 双向链表
 @param destroy 成员析构函数（free...）
 */
void dlist_init(DList *list, void (*destroy)(void *data));


/**
 销毁指定的双向链表 list - O(n)
 
 @param list 双向链表
 */
void dlist_destroy(DList *list);


/**
 在指定双向链表 list 中 element 后面插入一个新元素
 
 @param list 指定的双向链表 - O(1)
 @param element 新元素，如果为 NULL 则插入空链表中
 @param data 元素数据
 @return 成功返回 0，否则返回 -1
 */
int dlist_ins_next(DList *list, DListElmt *element, const void *data);


/**
 在指定双向链表 list 中 element 前面插入一个新元素
 
 @param list 指定的双向链表 - O(1)
 @param element 新元素，如果为 NULL 则插入空链表中
 @param data 元素数据
 @return 成功返回 0，否则返回 -1
 */
int dlist_ins_prev(DList *list, DListElmt *element, const void *data);

/**
 在指定双向链表 list 中移除 element 元素 - O(1)
 
 @param list 指定的双向链表
 @param element 待移除元素
 @param data 已移除元素的存储数据
 @return 成功返回 0，否则返回 -1
 */
int dlist_remove(DList *list, DListElmt *element, void **data);


/**
 获取指定双向链表 list 的长度 - O(1)
 
 @param list 指定的双向链表
 @return 双向链表中元素的个数
 */
#define dlist_size(list) ((list)->size)


/**
 获取指定双向链表 list 的头元素指针 - O(1)
 
 @param list 指定的双向链表
 @return 双向链表的头元素指针
 */
#define dlist_head(list) ((list)->head)


/**
 获取指定双向链表 list 的尾元素指针 - O(1)
 
 @param list 指定的双向链表
 @return 双向链表的尾元素指针
 */
#define dlist_tail(list) ((list)->tail)


/**
 判断元素 element 是否为指定双向链表 list 的头节点 - O(1)
 
 @param element 待判断的元素
 @return 是返回 1，否则返回 0
 */
#define dlist_is_head(element) ((element)->prev == NULL ? 1 : 0)


/**
 判断元素 element 是否为指定双向链表 list 的尾节点 - O(1)
 
 @param element 待判断的元素
 @return 是返回 1，否则返回 0
 */
#define dlist_is_tail(element) ((element)->next == NULL ? 1 : 0)


/**
 获取指定元素 element 中保存的数据 - O(1)
 
 @param element 指定的元素
 @return 结点保存的数据
 */
#define dlist_data(element) ((element)->data)


/**
 获取指定元素 element 中保存的下一个节点 - O(1)
 
 @param element 指定的元素
 @return 结点的下一个节点
 */
#define dlist_next(element) ((element)->next)

/**
 获取指定元素 element 中保存的上一个节点 - O(1)
 
 @param element 指定的元素
 @return 结点的上一个节点
 */
#define dlist_prev(element) ((element)->prev)

#endif /* DLIST_H */
