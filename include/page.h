//
//  page.h
//  Algorithms - second-chance page
//
//  Created by YourtionGuo on 24/04/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#ifndef PAGE_H
#define PAGE_H

#include "clist.h"

/**
 页
 */
typedef struct Page_
{
  int   number;
  int   reference;
  
} Page;


/**
 第二次机会置换法（时钟算法）LRU

 @param current 当前元素
 @return 页位置
 */
int replace_page(CListElmt **current);

#endif /* PAGE_H */
