//
//  bitree.h
//  Algorithms - binary tree
//
//  Created by YourtionGuo on 03/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#ifndef BITREE_H
#define BITREE_H

#include <stdlib.h>


/**
 二叉树结点
 */
typedef struct BiTreeNode_
{
  void               *data;
  struct BiTreeNode_ *left;
  struct BiTreeNode_ *right;
  
} BiTreeNode;


/**
 二叉树
 */
typedef struct BiTree_
{
  int         size;
  
  int         (*compare)(const void *key1, const void *key2);
  void        (*destroy)(void *data);
  
  BiTreeNode  *root;
  
} BiTree;


/**
 初始化由参数 tree 所指定二叉树 - O(1)

 @param tree 二叉树
 @param destroy 成员析构函数（free...）
 */
void bitree_init(BiTree *tree, void (*destroy)(void *data));


/**
 销毁由参数 tree 所指定二叉树 - O(n) n 为结点个数

 @param tree 二叉树
 */
void bitree_destroy(BiTree *tree);


/**
 在 tree 所指定二叉树中插入一个 node 所指定结点的左子结点 - O(1)

 @param tree 二叉树
 @param node 指定的结点
 @param data 结点数据
 @return 插入成功返回0；否则返回-1
 */
int bitree_ins_left(BiTree *tree, BiTreeNode *node, const void *data);


/**
 在 tree 所指定二叉树中插入一个 node 所指定结点的右子结点 - O(1)

 @param tree 二叉树
 @param node 指定的结点
 @param data 结点数据
 @return 插入成功返回0；否则返回-1
 */
int bitree_ins_right(BiTree *tree, BiTreeNode *node, const void *data);


/**
 移除由 tree 指定二叉树中 node 的左子结点为根的子树  - O(m) m 为子树结点个数

 @param tree 二叉树
 @param node 指定结点
 */
void bitree_rem_left(BiTree *tree, BiTreeNode *node);


/**
 移除由 tree 指定二叉树中 node 的右子结点为根的子树  - O(m) m 为子树结点个数

 @param tree 二叉树
 @param node 指定结点
 */
void bitree_rem_right(BiTree *tree, BiTreeNode *node);


/**
 将 left 和 right 所指定的两棵二叉树合并为单棵二叉树 - O(1)

 @param merge 合并后的树
 @param left 合并后左子树
 @param right 合并后右子树
 @param data 新树的根节点数据
 @return 合并成功，返回0；否则返回-1
 */
int bitree_merge(BiTree *merge, BiTree *left, BiTree *right, const void *data);


/**
 由参数 tree 所指定二叉树中的结点个数 - O(1)

 @param tree 二叉树
 @return 结点个数
 */
#define bitree_size(tree) ((tree)->size)


/**
 返回由参数 tree 所指定二叉树的根结点 - O(1)

 @param tree 二叉树
 @return 根结点
 */
#define bitree_root(tree) ((tree)->root)


/**
 判断由参数 node 所标识结点是否为二叉树中某个分支的结束 - O(1)

 @param node 待判断结点
 @return 分支结束则返回1；否则返回0
 */
#define bitree_is_eob(node) ((node) == NULL)


/**
 判断由参数 node 所指定结点是否为二叉树中的叶子结点 - O(1)

 @param node 待判断结点
 @return 叶子结点返回1；否则返回0
 */
#define bitree_is_leaf(node) ((node)->left == NULL && (node)->right == NULL)


/**
 返回由参数 node 所指定结点中存储的数据 - O(1)

 @param node 指定结点
 @return 结点中存储的数据
 */
#define bitree_data(node) ((node)->data)


/**
 返回由参数 node 所指定结点的左子结点 - O(1)

 @param node 指定结点
 @return 指定结点的左子结点
 */
#define bitree_left(node) ((node)->left)


/**
 返回由参数 node 所指定结点的右子结点 - O(1)
 
 @param node 指定结点
 @return 指定结点的右子结点
 */
#define bitree_right(node) ((node)->right)

#endif /* BITREE_H */
