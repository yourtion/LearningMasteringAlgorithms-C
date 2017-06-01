//
//  clist.h
//  Algorithms - circular list 
//
//  Created by YourtionGuo on 24/04/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#ifndef CLIST_H
#define CLIST_H

#include <stdlib.h>

/**
 循环链表结点
 */
typedef struct CListElmt_
{
  
  void               *data;
  struct CListElmt_  *next;
  
} CListElmt;

/**
 循环链表
 */
typedef struct CList_
{
  int         size;
  int         (*match)(const void *key1, const void *key2);
  void        (*destroy)(void *data);
  CListElmt   *head;
  
} CList;


/**
 初始化指定的循环链表 list - O(1)
 
 @param list 循环链表
 @param destroy 成员析构函数（free...）
 */
void clist_init(CList *list, void (*destroy)(void *data));


/**
 销毁指定的循环链表 list - O(n)
 
 @param list 循环链表
 */
void clist_destroy(CList *list);


/**
 在指定链表 list 中 element 后面插入一个新元素

 @param list 指定的循环链表
 @param element 指定的元素
 @param data 元素数据
 @return 成功返回 0，否则返回 -1
 */
int clist_ins_next(CList *list, CListElmt *element, const void *data);


/**
 在指定链表 list 中移除 element 后的元素 - O(1)
 
 @param list 指定的循环链表
 @param element 待移除元素前面的元素，如果为 NULL 则移除头部
 @param data 已移除元素的存储数据
 @return 成功返回 0，否则返回 -1
 */
int clist_rem_next(CList *list, CListElmt *element, void **data);


/**
 获取指定链表 list 的长度 - O(1)
 
 @param list 指定的循环链表
 @return 链表中元素的个数
 */
#define clist_size(list) ((list)->size)


/**
 获取指定链表 list 的头元素指针 - O(1)
 
 @param list 指定的循环链表
 @return 链表的头元素指针
 */
#define clist_head(list) ((list)->head)


/**
 获取指定元素 element 中保存的数据 - O(1)
 
 @param element 指定的元素
 @return 结点保存的数据
 */
#define clist_data(element) ((element)->data)


/**
 获取指定元素 element 中保存的下一个节点 - O(1)
 
 @param element 指定的元素
 @return 结点的下一个节点
 */
#define clist_next(element) ((element)->next)


#endif /* CLIST_H */
