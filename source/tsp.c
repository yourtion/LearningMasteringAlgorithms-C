//
//  tsp.c
//  Algorithms
//
//  Created by YourtionGuo on 24/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <float.h>
#include <math.h>
#include <stdlib.h>

#include "graph.h"
#include "graphalg.h"
#include "list.h"

#pragma mark - Public


int tsp(List *vertices, const TspVertex *start, List *tour,
        int (*match)(const void *key1, const void *key2))
{
  TspVertex   *tsp_vertex, *tsp_start, *selection = NULL;
  ListElmt    *element;
  double      minimum, distance, x = 0.0, y = 0.0;
  int         found, i;

  /// 初始化旅途结果列表
  list_init(tour, NULL);

  /// 初始化图的所有顶点

  found = 0;

  for (element = list_head(vertices); element != NULL; element = list_next(element)) {

    tsp_vertex = list_data(element);

    if (match(tsp_vertex, start)) {

      /// 从起点开始旅行

      if (list_ins_next(tour, list_tail(tour), tsp_vertex) != 0) {

        list_destroy(tour);
        return -1;
      }

      /// 保存其他及其坐标
      tsp_start = tsp_vertex;
      x = tsp_vertex->x;
      y = tsp_vertex->y;

      /// 将选中的顶点涂为黑色
      tsp_vertex->color = black;
      found = 1;

    } else {

      /// 将其它点涂为白色
      tsp_vertex->color = white;

    }
  }

  /// 如果找不到起点返回 -1
  if (!found) {

    list_destroy(tour);
    return -1;
  }

  /// 使用最近邻点法计算旅行路径

  i = 0;

  while (i < list_size(vertices) - 1) {

    /// 选择距离上一结点最近的白色顶点

    minimum = DBL_MAX;

    for (element = list_head(vertices); element != NULL; element = list_next(element)) {

      tsp_vertex = list_data(element);

      if (tsp_vertex->color == white) {

        distance = sqrt(pow(tsp_vertex->x-x,2.0) + pow(tsp_vertex->y-y,2.0));

        if (distance < minimum) {

          minimum = distance;
          selection = tsp_vertex;
        }
      }
    }

    /// 保存选中顶点的坐标
    x = selection->x;
    y = selection->y;

    /// 将选中的顶点涂为黑色
    selection->color = black;

    /// 插入选中顶点到旅途列表
    if (list_ins_next(tour, list_tail(tour), selection) != 0) {

      list_destroy(tour);
      return -1;
    }

    /// 准备选择下一个顶点
    i++;
  }

  /// 将起点插入旅途完成旅行
  if (list_ins_next(tour, list_tail(tour), tsp_start) != 0) {
    
    list_destroy(tour);
    return -1;
  }
  
  return 0;
}

