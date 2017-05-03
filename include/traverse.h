//
//  traverse.h
//  Algorithms - bitree traverse
//
//  Created by YourtionGuo on 03/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#ifndef TRAVERSE_H
#define TRAVERSE_H

#include "bitree.h"
#include "list.h"


/**
 前序方式来遍历表达式树

 @param node 根结点
 @param list 链表
 @return 操作成功返回0；否则返回-1
 */
int bitree_preorder(const BiTreeNode *node, List *list);


/**
 中序式来遍历表达式树

 @param node 根结点
 @param list 链表
 @return 操作成功返回0；否则返回-1
 */
int bitree_inorder(const BiTreeNode *node, List *list);


/**
 后序方式来遍历表达式树

 @param node 根结点
 @param list 链表
 @return 操作成功返回0；否则返回-1
 */
int bitree_postorder(const BiTreeNode *node, List *list);

#endif /* TRAVERSE_H */
