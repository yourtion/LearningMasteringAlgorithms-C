//
//  shortest.c
//  Algorithms - Shortest paths (Dijkstra)
//
//  Created by YourtionGuo on 24/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <float.h>
#include <stdlib.h>

#include "graph.h"
#include "graphalg.h"
#include "list.h"
#include "set.h"

#pragma mark - Private


/**
 释放所选顶点与相邻顶点间的边

 @param u 顶点 1
 @param v 顶点 2
 @param weight 权重
 */
static void relax(PathVertex *u, PathVertex *v, double weight)
{
  /// 释放顶点 u 和 v 之间的边

  if (v->d > u->d + weight) {

    v->d = u->d + weight;
    v->parent = u;
  }
  return;
}


#pragma mark - Public


int shortest(Graph *graph, const PathVertex *start, List *paths,
             int (*match)(const void *key1, const void *key2))
{
  AdjList       *adjlist = NULL;
  PathVertex    *pth_vertex, *adj_vertex;
  ListElmt      *element, *member;
  double        minimum;
  int           found, i;

  /// 初始化图的所有顶点

  found = 0;

  for (element = list_head(&graph_adjlists(graph)); element != NULL; element = list_next(element)) {

    pth_vertex = ((AdjList *)list_data(element))->vertex;

    if (match(pth_vertex, start)) {

      /// 初始化起点

      pth_vertex->color = white;
      pth_vertex->d = 0;
      pth_vertex->parent = NULL;
      found = 1;

    } else {

      /// 初始化起点外的其他顶点

      pth_vertex->color = white;
      pth_vertex->d = DBL_MAX;
      pth_vertex->parent = NULL;

    }
  }

  /// 如果找不到起点返回 -1

  if (!found) return -1;

  /// 使用 Dijkstra 算法计算最短路径

  i = 0;

  while (i < graph_vcount(graph)) {

    /// 选择最短路径的白色顶点

    minimum = DBL_MAX;

    for (element = list_head(&graph_adjlists(graph)); element != NULL; element = list_next(element)) {

      pth_vertex = ((AdjList *)list_data(element))->vertex;

      if (pth_vertex->color == white && pth_vertex->d < minimum) {

        minimum = pth_vertex->d;
        adjlist = list_data(element);
      }
    }

    /// 将选中的顶点涂为黑色
    ((PathVertex *)adjlist->vertex)->color = black;

    /// 遍历选中顶点的每个邻接顶点

    for (member = list_head(&adjlist->adjacent); member != NULL; member = list_next(member)) {

      adj_vertex = list_data(member);

      /// 通过顶点的邻接表找到邻接顶点

      for (element = list_head(&graph_adjlists(graph)); element != NULL; element = list_next(element)) {

        pth_vertex = ((AdjList *)list_data(element))->vertex;

        if (match(pth_vertex, adj_vertex)) {

          /// 释放邻接表中的邻接顶点
          relax(adjlist->vertex, pth_vertex, adj_vertex->weight);

        }
      }
    }

    /// 准备选择下一个顶点
    i++;
  }

  /// 将最短路径载入列表
  list_init(paths, NULL);

  for (element = list_head(&graph_adjlists(graph)); element != NULL; element = list_next(element)) {

    /// 从邻接表中加载每个黑色顶点
    pth_vertex = ((AdjList *)list_data(element))->vertex;
    
    if (pth_vertex->color == black) {
      
      if (list_ins_next(paths, list_tail(paths), pth_vertex) != 0) {
        
        list_destroy(paths);
        return -1;
      }
    }
  }
  
  return 0;
}
