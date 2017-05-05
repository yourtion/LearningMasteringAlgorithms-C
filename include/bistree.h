//
//  bistree.h
//  Algorithms - binary search tree AVL树（Adel'son-Vel'skii and Landis）
//
//  Created by YourtionGuo on 04/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#ifndef BISTREE_H
#define BISTREE_H

#include "bitree.h"

/// 定义平衡参数
#define   AVL_LFT_HEAVY   1
#define   AVL_BALANCED    0
#define   AVL_RGT_HEAVY   -1


/**
 自平衡二叉搜索树结点
 */
typedef struct AvlNode_
{
  void    *data;
  int     hidden;
  int     factor;

} AvlNode;


/**
 自平衡二叉搜索树
 */
typedef BiTree BisTree;


/**
 初始化由参数 tree 所指定二叉搜索树 - O(1)

 @param tree 二叉搜索树
 @param compare 函数指针，用于比较两个成员大小（大于返回 1，小于返回 -1，等于返回 0）
 @param destroy 成员析构函数（free...）
 */
void bistree_init(BisTree *tree,
                  int (*compare)(const void *key1, const void *key2),
                  void (*destroy)(void *data));


/**
 销毁由参数 tree 所指定二叉搜索树 - O(n)

 @param tree 二叉搜索树
 */
void bistree_destroy(BisTree *tree);


/**
 将结点插入由参数 tree 所指定二叉搜索树中 - O(lg n)

 @param tree 二叉搜索树
 @param data 结点数据
 @return 插入成功，返回0；已存在，返回1；否则返回-1
 */
int bistree_insert(BisTree *tree, const void *data);


/**
 在由参数 tree 所指定二叉搜索树中移除数据 data 相吻合的结点 - O(lg n)

 @param tree 二叉搜索树
 @param data 已移除结点的存储数据
 @return 移除成功，返回0；否则返回-1
 */
int bistree_remove(BisTree *tree, const void *data);


/**
 判断由参数 tree 所指定二叉搜索树中是否存在同参数 data 相吻合的结点 - O(lg n)

 @param tree 二叉搜索树
 @param data 结点数据
 @return 查找到结点，返回0；否则返回-1
 */
int bistree_lookup(BisTree *tree, void **data);


/**
 由参数 tree 所指定二叉搜索树中的结点个数 - O(1)

 @param tree 二叉搜索树
 @return 结点个数
 */
#define bistree_size(tree) ((tree)->size)

#endif /* bistree_h */
