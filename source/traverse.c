//
//  traverse.c
//  Algorithms - bitree traverse
//
//  Created by YourtionGuo on 03/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include "list.h"
#include "traverse.h"

#pragma mark - Public


int bitree_preorder(const BiTreeNode *node, List *list)
{
  if (!bitree_is_eob(node)) {
    
    if (list_ins_next(list, list_tail(list), bitree_data(node)) != 0) return -1;
    
    if (!bitree_is_eob(bitree_left(node))) {
      if (bitree_preorder(bitree_left(node), list) != 0) return -1;
    }
    
    if (!bitree_is_eob(bitree_right(node))) {
      if (bitree_preorder(bitree_right(node), list) != 0) return -1;
    }
    
  }
  
  return 0;
}


int bitree_inorder(const BiTreeNode *node, List *list)
{
  if (!bitree_is_eob(node)) {
    
    if (!bitree_is_eob(bitree_left(node))) {
      if (bitree_inorder(bitree_left(node), list) != 0) return -1;
    }
    
    if (list_ins_next(list, list_tail(list), bitree_data(node)) != 0) return -1;
    
    if (!bitree_is_eob(bitree_right(node))) {
      if (bitree_inorder(bitree_right(node), list) != 0) return -1;
    }
    
  }
  
  return 0;
}


int bitree_postorder(const BiTreeNode *node, List *list)
{
  if (!bitree_is_eob(node)) {
    
    if (!bitree_is_eob(bitree_left(node))) {
      if (bitree_postorder(bitree_left(node), list) != 0) return -1;
    }
    
    if (!bitree_is_eob(bitree_right(node))) {
      if (bitree_postorder(bitree_right(node), list) != 0) return -1;
    }
    
    if (list_ins_next(list, list_tail(list), bitree_data(node)) != 0) return -1;
    
  }
  
  return 0;
}
