//
//  main.c
//  MasteringAlgorithms
//  Illustrates using a binary search tree (see Chapter 9).
//
//  Created by YourtionGuo on 04/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bistree.h"

/// 定义字符串长度
#define     STRSIZ      6

static void preorder_tree(const BiTreeNode *node)
{
  /// 通过制定的根节点打印搜索二叉树

  if (!bitree_is_eob(node)) {

    fprintf(stdout, "-> Node=%s, %+2d, hidden=%d\n",
            (char *)((AvlNode *) bitree_data(node))->data,
            ((AvlNode *)bitree_data(node))->factor,
            ((AvlNode *)bitree_data(node))->hidden);

    if (!bitree_is_eob(bitree_left(node))) preorder_tree(bitree_left(node));

    if (!bitree_is_eob(bitree_right(node))) preorder_tree(bitree_right(node));

  }

  return;
}


static int compare_str(const void *str1, const void *str2)
{
  int     retval;

  /// 字符串对比函数

  if ((retval = strcmp((const char *)str1, (const char *)str2)) > 0) return 1;
  if (retval < 0) return -1;

  return 0;
}


/// 搜索词定义
typedef enum Words_ {hop, hat, tap, bat, tip, mop, mom, cat, zoo, wax, top, dip} Words;


int main(int argc, char **argv)
{
  BiTree      tree;

  char        *target;

  char        sarray[12][STRSIZ], tarray[12][STRSIZ];

  /// 初始化搜索词
  strcpy(sarray[hop], "hop");
  strcpy(sarray[hat], "hat");
  strcpy(sarray[tap], "tap");
  strcpy(sarray[bat], "bat");
  strcpy(sarray[tip], "tip");
  strcpy(sarray[mop], "mop");
  strcpy(sarray[mom], "mom");
  strcpy(sarray[cat], "cat");
  strcpy(sarray[zoo], "zoo");
  strcpy(sarray[wax], "wax");
  strcpy(sarray[top], "top");
  strcpy(sarray[dip], "dip");


  /// 初始化搜索二叉树
  bistree_init(&tree, compare_str, NULL);

  /// 执行搜索二叉树操作

  fprintf(stdout, "Inserting some nodes\n");

  if (bistree_insert(&tree, sarray[tap]) != 0) return 1;

  fprintf(stdout, "Tree size is %d\n", bistree_size(&tree));
  fprintf(stdout, "(Preorder traversal)\n");
  preorder_tree(bitree_root(&tree));

  if (bistree_insert(&tree, sarray[tip]) != 0) return 1;

  fprintf(stdout, "Tree size is %d\n", bistree_size(&tree));
  fprintf(stdout, "(Preorder traversal)\n");
  preorder_tree(bitree_root(&tree));

  if (bistree_insert(&tree, sarray[top]) != 0) return 1;

  fprintf(stdout, "Tree size is %d\n", bistree_size(&tree));
  fprintf(stdout, "(Preorder traversal)\n");
  preorder_tree(bitree_root(&tree));

  if (bistree_insert(&tree, sarray[cat]) != 0) return 1;

  fprintf(stdout, "Tree size is %d\n", bistree_size(&tree));
  fprintf(stdout, "(Preorder traversal)\n");
  preorder_tree(bitree_root(&tree));

  if (bistree_insert(&tree, sarray[bat]) != 0) return 1;

  fprintf(stdout, "Tree size is %d\n", bistree_size(&tree));
  fprintf(stdout, "(Preorder traversal)\n");
  preorder_tree(bitree_root(&tree));

  fprintf(stdout, "Removing %s\n", sarray[tap]);

  if (bistree_remove(&tree, &sarray[tap]) != 0) {

    fprintf(stdout, "Could not find %s\n", sarray[tap]);
    
  } else {

    fprintf(stdout, "Tree size is %d\n", bistree_size(&tree));
    fprintf(stdout, "(Preorder traversal)\n");
    preorder_tree(bitree_root(&tree));

  }

  fprintf(stdout, "Removing %s\n", sarray[top]);

  if (bistree_remove(&tree, &sarray[top]) != 0) {

    fprintf(stdout, "Could not find %s\n", sarray[top]);

  } else {

    fprintf(stdout, "Tree size is %d\n", bistree_size(&tree));
    fprintf(stdout, "(Preorder traversal)\n");
    preorder_tree(bitree_root(&tree));

  }

  fprintf(stdout, "Removing %s\n", sarray[tip]);

  if (bistree_remove(&tree, &sarray[tip]) != 0) {

    fprintf(stdout, "Could not find %s\n", sarray[tip]);

  } else {

    fprintf(stdout, "Tree size is %d\n", bistree_size(&tree));
    fprintf(stdout, "(Preorder traversal)\n");
    preorder_tree(bitree_root(&tree));

  }

  fprintf(stdout, "Removing %s\n", sarray[hop]);

  if (bistree_remove(&tree, &sarray[hop]) != 0) {

    fprintf(stdout, "Could not find %s\n", sarray[hop]);

  } else {

    fprintf(stdout, "Tree size is %d\n", bistree_size(&tree));
    fprintf(stdout, "(Preorder traversal)\n");
    preorder_tree(bitree_root(&tree));

  }

  fprintf(stdout, "Inserting %s\n", sarray[hop]);

  if (bistree_insert(&tree, sarray[hop]) != 0) return 1;

  fprintf(stdout, "Tree size is %d\n", bistree_size(&tree));
  fprintf(stdout, "(Preorder traversal)\n");
  preorder_tree(bitree_root(&tree));

  fprintf(stdout, "Inserting %s\n", sarray[dip]);

  if (bistree_insert(&tree, sarray[dip]) != 0) return 1;

  fprintf(stdout, "Tree size is %d\n", bistree_size(&tree));
  fprintf(stdout, "(Preorder traversal)\n");
  preorder_tree(bitree_root(&tree));

  fprintf(stdout, "Inserting %s\n", sarray[tap]);

  if (bistree_insert(&tree, sarray[tap]) != 0) return 1;

  fprintf(stdout, "Tree size is %d\n", bistree_size(&tree));
  fprintf(stdout, "(Preorder traversal)\n");
  preorder_tree(bitree_root(&tree));

  fprintf(stdout, "Inserting %s\n", sarray[top]);

  if (bistree_insert(&tree, sarray[top]) != 0) return 1;

  fprintf(stdout, "Tree size is %d\n", bistree_size(&tree));
  fprintf(stdout, "(Preorder traversal)\n");
  preorder_tree(bitree_root(&tree));

  fprintf(stdout, "Inserting %s\n", sarray[tip]);

  if (bistree_insert(&tree, sarray[tip]) != 0) return 1;

  fprintf(stdout, "Tree size is %d\n", bistree_size(&tree));
  fprintf(stdout, "(Preorder traversal)\n");
  preorder_tree(bitree_root(&tree));

  fprintf(stdout, "Inserting more nodes\n");

  if (bistree_insert(&tree, sarray[mom]) != 0) return 1;

  fprintf(stdout, "Tree size is %d\n", bistree_size(&tree));
  fprintf(stdout, "(Preorder traversal)\n");
  preorder_tree(bitree_root(&tree));

  if (bistree_insert(&tree, sarray[hat]) != 0) return 1;

  fprintf(stdout, "Tree size is %d\n", bistree_size(&tree));
  fprintf(stdout, "(Preorder traversal)\n");
  preorder_tree(bitree_root(&tree));

  if (bistree_insert(&tree, sarray[mop]) != 0) return 1;

  fprintf(stdout, "Tree size is %d\n", bistree_size(&tree));
  fprintf(stdout, "(Preorder traversal)\n");
  preorder_tree(bitree_root(&tree));

  if (bistree_insert(&tree, sarray[wax]) != 0) return 1;

  fprintf(stdout, "Tree size is %d\n", bistree_size(&tree));
  fprintf(stdout, "(Preorder traversal)\n");
  preorder_tree(bitree_root(&tree));

  if (bistree_insert(&tree, sarray[zoo]) != 0) return 1;

  fprintf(stdout, "Tree size is %d\n", bistree_size(&tree));
  fprintf(stdout, "(Preorder traversal)\n");
  preorder_tree(bitree_root(&tree));

  fprintf(stdout, "Removing %s\n", sarray[wax]);

  if (bistree_remove(&tree, &sarray[wax]) != 0) {

    fprintf(stdout, "Could not find %s\n", sarray[wax]);

  } else {

    fprintf(stdout, "Tree size is %d\n", bistree_size(&tree));
    fprintf(stdout, "(Preorder traversal)\n");
    preorder_tree(bitree_root(&tree));

  }

  fprintf(stdout, "Removing %s\n", sarray[hop]);

  if (bistree_remove(&tree, &sarray[hop]) != 0) {

    fprintf(stdout, "Could not find %s\n", sarray[hop]);

  } else {

    fprintf(stdout, "Tree size is %d\n", bistree_size(&tree));
    fprintf(stdout, "(Preorder traversal)\n");
    preorder_tree(bitree_root(&tree));

  }

  fprintf(stdout, "Looking up some nodes\n");

  strcpy(tarray[0], "top");
  strcpy(tarray[1], "hop");
  strcpy(tarray[2], "wax");
  strcpy(tarray[3], "hat");
  strcpy(tarray[4], "xxx");

  target = tarray[0];

  if (bistree_lookup(&tree, (void **)&target) == -1) {
    fprintf(stdout, "Could not find %s\n", target);
  } else {
    fprintf(stdout, "Found %s\n", target);
  }

  target = tarray[1];

  if (bistree_lookup(&tree, (void **)&target) == -1) {
    fprintf(stdout, "Could not find %s\n", target);
  } else {
    fprintf(stdout, "Found %s\n", target);
  }

  target = tarray[2];

  if (bistree_lookup(&tree, (void **)&target) == -1) {
    fprintf(stdout, "Could not find %s\n", target);
  } else {
    fprintf(stdout, "Found %s\n", target);
  }

  target = tarray[3];

  if (bistree_lookup(&tree, (void **)&target) == -1) {
    fprintf(stdout, "Could not find %s\n", target);
  } else {
    fprintf(stdout, "Found %s\n", target);
  }
  
  target = tarray[4];
  
  if (bistree_lookup(&tree, (void **)&target) == -1) {
    fprintf(stdout, "Could not find %s\n", target);
  } else {
    fprintf(stdout, "Found %s\n", target);
  }

  /// 销毁搜索二叉树
  fprintf(stdout, "Destroying the search tree\n");
  bistree_destroy(&tree);
  
  return 0;
}
