//
//  page.c
//  Algorithms - second-chance page
//
//  Created by YourtionGuo on 24/04/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include "clist.h"
#include "page.h"

#pragma mark - Public


int replace_page(CListElmt **current)
{
  /// 循环整个链表直至找到结果
  
  while (((Page *)(*current)->data)->reference != 0) {
    
    ((Page *)(*current)->data)->reference = 0;
    *current = clist_next(*current);
    
  }
  
  return ((Page *)(*current)->data)->number;
}
