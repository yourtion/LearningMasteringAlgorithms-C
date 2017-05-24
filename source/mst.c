//
//  mst.c
//  Algorithms - Minimum spanning tree
//
//  Created by YourtionGuo on 23/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <float.h>
#include <stdlib.h>

#include "graph.h"
#include "graphalg.h"
#include "list.h"


int mst(Graph *graph, const MstVertex *start, List *span,
        int (*match)(const void *key1, const void *key2))
{
  AdjList     *adjlist = NULL;
  MstVertex   *mst_vertex, *adj_vertex;
  ListElmt    *element, *member;
  double      minimum;
  int         found, i;

  /// 初始化图的所有顶点

  found = 0;

  for (element = list_head(&graph_adjlists(graph)); element != NULL; element = list_next(element)) {

    mst_vertex = ((AdjList *)list_data(element))->vertex;

    if (match(mst_vertex, start)) {

      /// 初始化起点
      mst_vertex->color = white;
      mst_vertex->key = 0;
      mst_vertex->parent = NULL;
      found = 1;

    } else {

      /// 初始化起点外的其他顶点
      mst_vertex->color = white;
      mst_vertex->key = DBL_MAX;
      mst_vertex->parent = NULL;

    }
  }

  /// 如果找不到起点返回 -1
  if (!found) return -1;

  /// 使用 Prim 算法计算最小生成树

  i = 0;

  while (i < graph_vcount(graph)) {

    /// 选择最小权重的白色顶点
    minimum = DBL_MAX;

    for (element = list_head(&graph_adjlists(graph)); element != NULL; element = list_next(element)) {

      mst_vertex = ((AdjList *)list_data(element))->vertex;

      if (mst_vertex->color == white && mst_vertex->key < minimum) {

        minimum = mst_vertex->key;
        adjlist = list_data(element);

      }
    }

    /// 将选中的顶点涂为黑色
    ((MstVertex *)adjlist->vertex)->color = black;

    /// 遍历选中顶点的每个邻接顶点
    for (member = list_head(&adjlist->adjacent); member != NULL; member = list_next(member)) {

      adj_vertex = list_data(member);

      /// 通过顶点的邻接表找到邻接顶点
      for (element = list_head(&graph_adjlists(graph)); element != NULL; element = list_next(element)) {

        mst_vertex = ((AdjList *)list_data(element))->vertex;

        if (match(mst_vertex, adj_vertex)) {

          /// 决定是否改变邻接表中邻接顶点的权重和父节点
          if (mst_vertex->color == white && adj_vertex->weight < mst_vertex->key) {

            mst_vertex->key = adj_vertex->weight;
            mst_vertex->parent = adjlist->vertex;

          }

          break;

        }
      }
    }

    /// 准备选择下一个顶点
    i++;
  }

  /// 将最小生成树载入列表

  list_init(span, NULL);

  for (element = list_head(&graph_adjlists(graph)); element != NULL; element = list_next(element)) {

    /// 从邻接表中加载每个黑色顶点
    mst_vertex = ((AdjList *)list_data(element))->vertex;
    
    if (mst_vertex->color == black) {
      
      if (list_ins_next(span, list_tail(span), mst_vertex) != 0) {
        
        list_destroy(span);
        return -1;
      }
    }
  }
  
  return 0;
}
