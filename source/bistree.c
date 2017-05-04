//
//  bistree.c
//  Algorithms - binary search tree AVL树（Adel'son-Vel'skii and Landis）
//
//  Created by YourtionGuo on 04/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <stdlib.h>
#include <string.h>

#include "bistree.h"

#pragma mark - Private


static void destroy_right(BisTree *tree, BiTreeNode *node);


/**
 执行左旋转

 @param node 二叉树结点
 */
static void rotate_left(BiTreeNode **node)
{
  BiTreeNode    *left, *grandchild;

  left = bitree_left(*node);

  if (((AvlNode *)bitree_data(left))->factor == AVL_LFT_HEAVY) {

    /// 执行 LL ( Left-Left ) 旋转操作

    bitree_left(*node) = bitree_right(left);
    bitree_right(left) = *node;
    ((AvlNode *)bitree_data(*node))->factor = AVL_BALANCED;
    ((AvlNode *)bitree_data(left))->factor = AVL_BALANCED;
    *node = left;

  } else {

    /// 执行 LR ( Left-Right ) 旋转操作

    grandchild = bitree_right(left);
    bitree_right(left) = bitree_left(grandchild);
    bitree_left(grandchild) = left;
    bitree_left(*node) = bitree_right(grandchild);
    bitree_right(grandchild) = *node;

    switch (((AvlNode *)bitree_data(grandchild))->factor) {

      case AVL_LFT_HEAVY:

        ((AvlNode *)bitree_data(*node))->factor = AVL_RGT_HEAVY;
        ((AvlNode *)bitree_data(left))->factor = AVL_BALANCED;
        break;

      case AVL_BALANCED:

        ((AvlNode *)bitree_data(*node))->factor = AVL_BALANCED;
        ((AvlNode *)bitree_data(left))->factor = AVL_BALANCED;
        break;

      case AVL_RGT_HEAVY:

        ((AvlNode *)bitree_data(*node))->factor = AVL_BALANCED;
        ((AvlNode *)bitree_data(left))->factor = AVL_LFT_HEAVY;
        break;

    }

    ((AvlNode *)bitree_data(grandchild))->factor = AVL_BALANCED;
    *node = grandchild;
  }

  return;
}


/**
 执行右旋转

 @param node 二叉树结点
 */
static void rotate_right(BiTreeNode **node)
{
  BiTreeNode    *right, *grandchild;

  right = bitree_right(*node);

  if (((AvlNode *)bitree_data(right))->factor == AVL_RGT_HEAVY) {

    /// 执行 RR ( Right-Right ) 旋转操作

    bitree_right(*node) = bitree_left(right);
    bitree_left(right) = *node;
    ((AvlNode *)bitree_data(*node))->factor = AVL_BALANCED;
    ((AvlNode *)bitree_data(right))->factor = AVL_BALANCED;
    *node = right;

  } else {

    /// 执行 RR ( Right-Right ) 旋转操作

    grandchild = bitree_left(right);
    bitree_left(right) = bitree_right(grandchild);
    bitree_right(grandchild) = right;
    bitree_right(*node) = bitree_left(grandchild);
    bitree_left(grandchild) = *node;

    switch (((AvlNode *)bitree_data(grandchild))->factor) {

      case AVL_LFT_HEAVY:

        ((AvlNode *)bitree_data(*node))->factor = AVL_BALANCED;
        ((AvlNode *)bitree_data(right))->factor = AVL_RGT_HEAVY;
        break;

      case AVL_BALANCED:

        ((AvlNode *)bitree_data(*node))->factor = AVL_BALANCED;
        ((AvlNode *)bitree_data(right))->factor = AVL_BALANCED;
        break;

      case AVL_RGT_HEAVY:

        ((AvlNode *)bitree_data(*node))->factor = AVL_LFT_HEAVY;
        ((AvlNode *)bitree_data(right))->factor = AVL_BALANCED;
        break;

    }

    ((AvlNode *)bitree_data(grandchild))->factor = AVL_BALANCED;
    *node = grandchild;
  }

  return;
}


/**
 移除由 tree 指定二叉树中 node 的左子结点为根的子树

 @param tree 搜索二叉树
 @param node 指定结点
 */
static void destroy_left(BisTree *tree, BiTreeNode *node)
{
  BiTreeNode    **position;

  /// 不允许在空树中执行移除
  if (bitree_size(tree) == 0) return;

  /// 确定移除结点的位置
  if (node == NULL) {
    position = &tree->root;
  } else {
    position = &node->left;
  }

  /// 移除结点
  if (*position != NULL) {

    destroy_left(tree, *position);
    destroy_right(tree, *position);

    if (tree->destroy != NULL) {
      /// 执行用户指定的 destroy 函数
      tree->destroy(((AvlNode *)(*position)->data)->data);
    }

    /// 清理 AVL 数据结构和结点数据
    free((*position)->data);
    free(*position);
    *position = NULL;

    /// 更新树的 size
    tree->size--;
  }

  return;
}



/**
 移除由 tree 指定二叉树中 node 的右子结点为根的子树

 @param tree 搜索二叉树
 @param node 指定结点
 */
static void destroy_right(BisTree *tree, BiTreeNode *node)
{
  BiTreeNode         **position;

  /// 不允许在空树中执行移除
  if (bitree_size(tree) == 0) return;

  /// 确定移除结点的位置
  if (node == NULL) {
    position = &tree->root;
  } else {
    position = &node->right;
  }

  /// 移除结点
  if (*position != NULL) {

    destroy_left(tree, *position);
    destroy_right(tree, *position);

    if (tree->destroy != NULL) {
      /// 执行用户指定的 destroy 函数
      tree->destroy(((AvlNode *)(*position)->data)->data);
    }

    /// 清理 AVL 数据结构和结点数据
    free((*position)->data);
    free(*position);
    *position = NULL;

    /// 更新树的 size
    tree->size--;
  }

  return;
}


/**
 在 tree 所指定二叉树中插入一个 node 所指定结点

 @param tree 二叉搜索树
 @param node 指定的结点
 @param data 结点数据
 @param balanced 是否已经平衡（已平衡为 1，未平衡为 0）
 @return 插入成功，返回0；已存在，返回1；否则返回-1
 */
static int insert(BisTree *tree, BiTreeNode **node, const void *data, int *balanced)
{
  AvlNode   *avl_data;
  int       cmpval, retval;

  /// 将数据插入到树中

  if (bitree_is_eob(*node)) {

    /// 处理插入空树的情况

    if ((avl_data = (AvlNode *)malloc(sizeof(AvlNode))) == NULL) return -1;

    avl_data->factor = AVL_BALANCED;
    avl_data->hidden = 0;
    avl_data->data = (void *)data;

    return bitree_ins_left(tree, *node, avl_data);

  } else {

    /// 处理非空树情况

    cmpval = tree->compare(data, ((AvlNode *)bitree_data(*node))->data);

    if (cmpval < 0) {

      /// 处理左子树

      if (bitree_is_eob(bitree_left(*node))) {

        if ((avl_data = (AvlNode *)malloc(sizeof(AvlNode))) == NULL) return -1;

        avl_data->factor = AVL_BALANCED;
        avl_data->hidden = 0;
        avl_data->data = (void *)data;

        if (bitree_ins_left(tree, *node, avl_data) != 0) return -1;

        *balanced = 0;

      } else {

        if ((retval = insert(tree, &bitree_left(*node), data, balanced)) != 0) return retval;
      }

      /// 确保树依然保持平衡
      if (!(*balanced)) {

        switch (((AvlNode *)bitree_data(*node))->factor) {

          case AVL_LFT_HEAVY:

            rotate_left(node);
            *balanced = 1;
            break;

          case AVL_BALANCED:

            ((AvlNode *)bitree_data(*node))->factor = AVL_LFT_HEAVY;
            break;

          case AVL_RGT_HEAVY:

            ((AvlNode *)bitree_data(*node))->factor = AVL_BALANCED;
            *balanced = 1;

        }
      }

    } else if (cmpval > 0) {

      /// 处理右子树

      if (bitree_is_eob(bitree_right(*node))) {

        if ((avl_data = (AvlNode *)malloc(sizeof(AvlNode))) == NULL)
          return -1;

        avl_data->factor = AVL_BALANCED;
        avl_data->hidden = 0;
        avl_data->data = (void *)data;

        if (bitree_ins_right(tree, *node, avl_data) != 0)
          return -1;

        *balanced = 0;

      } else {

        if ((retval = insert(tree, &bitree_right(*node), data, balanced)) != 0) return retval;
      }

      /// 确保树依然保持平衡
      if (!(*balanced)) {

        switch (((AvlNode *)bitree_data(*node))->factor) {

          case AVL_LFT_HEAVY:

            ((AvlNode *)bitree_data(*node))->factor = AVL_BALANCED;
            *balanced = 1;
            break;

          case AVL_BALANCED:

            ((AvlNode *)bitree_data(*node))->factor = AVL_RGT_HEAVY;
            break;

          case AVL_RGT_HEAVY:

            rotate_right(node);
            *balanced = 1;

        }
      }

    } else {

      /// 处理找到节点的情况

      ///如果找到非隐藏节点直接返回 1
      if (!((AvlNode *)bitree_data(*node))->hidden) return 1;

      ///插入新数据并取消隐藏
      if (tree->destroy != NULL) {
        /// 销毁隐藏节点的数据
        tree->destroy(((AvlNode *)bitree_data(*node))->data);
      }

      ((AvlNode *)bitree_data(*node))->data = (void *)data;
      ((AvlNode *)bitree_data(*node))->hidden = 0;

      ///如果是隐藏节点数据替换，则不需要再次平衡树
      *balanced = 1;
    }
  }

  return 0;
}


/**
 在 tree 所指定二叉树中隐藏一个 node 所指定结点

 @param tree 二叉搜索树
 @param node 指定的结点
 @param data 结点数据
 @return 成功返回0；否则返回-1
 */
static int hide(BisTree *tree, BiTreeNode *node, const void *data)
{
  int     cmpval, retval;

  /// 没找到节点返回 -1
  if (bitree_is_eob(node)) return -1;

  cmpval = tree->compare(data, ((AvlNode *)bitree_data(node))->data);

  if (cmpval < 0) {

    /// 处理左子树
    retval = hide(tree, bitree_left(node), data);

  } else if (cmpval > 0) {

    /// 处理右子树
    retval = hide(tree, bitree_right(node), data);

  } else {

    /// 将节点标记为隐藏
    ((AvlNode *)bitree_data(node))->hidden = 1;
    retval = 0;
  }

  return retval;
}


/**
 在 tree 所指定二叉搜索树中查找 node 指定的节点

 @param tree 二叉搜索树
 @param node 指定的结点
 @param data 找到的结点数据
 @return 找到返回0；否则返回-1
 */
static int lookup(BisTree *tree, BiTreeNode *node, void **data)
{
  int     cmpval, retval;

  /// 没找到节点返回 -1
  if (bitree_is_eob(node)) return -1;

  cmpval = tree->compare(*data, ((AvlNode *)bitree_data(node))->data);

  if (cmpval < 0) {

    /// 处理左子树
    retval = lookup(tree, bitree_left(node), data);

  } else if (cmpval > 0) {

    /// 处理右子树
    retval = lookup(tree, bitree_right(node), data);

  } else {

    if (!((AvlNode *)bitree_data(node))->hidden) {

      /// 将找到的节点数据返回
      *data = ((AvlNode *)bitree_data(node))->data;
      retval = 0;

    } else {

      /// 没找到节点返回 -1
      return -1;
    }
  }

  return retval;
}

#pragma mark - Public

void bistree_init(BisTree *tree,
                  int (*compare)(const void *key1, const void *key2),
                  void (*destroy)(void *data))
{
  /// 初始化搜索二叉树
  bitree_init(tree, destroy);
  tree->compare = compare;

  return;
}


void bistree_destroy(BisTree *tree)
{
  /// 删除所有树的结点
  destroy_left(tree, NULL);

  /// 清理二叉树数据结构
  memset(tree, 0, sizeof(BisTree));
  
  return;
}


int bistree_insert(BisTree *tree, const void *data)
{
  int     balanced = 0;
  return insert(tree, &bitree_root(tree), data, &balanced);
}


int bistree_remove(BisTree *tree, const void *data)
{
  return hide(tree, bitree_root(tree), data);
}


int bistree_lookup(BisTree *tree, void **data)
{
  return lookup(tree, bitree_root(tree), data);
  
}
