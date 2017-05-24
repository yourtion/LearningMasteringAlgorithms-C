//
//  route.c
//  Algorithms - Route SPF
//
//  Created by YourtionGuo on 24/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <stdlib.h>

#include "graphalg.h"
#include "list.h"
#include "route.h"

#pragma mark - Public

int route(List *paths, PathVertex *destination, PathVertex **next,
          int(*match)(const void *key1, const void *key2))
{
  PathVertex    *temp = NULL, *parent = NULL;
  ListElmt      *element;
  int           found;

  /// 在网关列表中找到目的结点

  found = 0;

  for (element = list_head(paths); element != NULL; element = list_next(element)) {

    if (match(list_data(element), destination)) {

      temp = list_data(element);
      parent = ((PathVertex *)list_data(element))->parent;
      found = 1;
      break;
    }
  }

  /// 如果找不到目标结点返回 -1
  if (!found) return -1;

  /// 计算到目标结点最短路径的下一网关

  while (parent != NULL) {

    temp = list_data(element);
    found = 0;

    for (element = list_head(paths); element != NULL; element = list_next(element)) {

      if (match(list_data(element), parent)) {

        parent = ((PathVertex *)list_data(element))->parent;
        found = 1;
        break;
      }
    }

    /// 结点不可达返回 -1
    if (!found) return -1;
    
  }

  *next = temp;
  
  return 0;
}
