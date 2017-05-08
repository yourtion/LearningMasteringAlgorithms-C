//
//  bfs.c
//  Algorithms - Graph breadth-first search
//
//  Created by YourtionGuo on 08/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <stdlib.h>

#include "bfs.h"
#include "graph.h"
#include "list.h"
#include "queue.h"

#pragma mark - Public

int bfs(Graph *graph, BfsVertex *start, List *hops)
{
  Queue       queue;
  AdjList     *adjlist, *clr_adjlist;
  BfsVertex   *clr_vertex, *adj_vertex;
  ListElmt    *element, *member;

  /// 初始化图的所有顶点

  for (element = list_head(&graph_adjlists(graph)); element != NULL; element = list_next(element)) {

    clr_vertex = ((AdjList *)list_data(element))->vertex;

    if (graph->match(clr_vertex, start)) {

      /// 初始化起点
      clr_vertex->color = gray;
      clr_vertex->hops = 0;

    } else {

      /// 初始化其他顶点
      clr_vertex->color = white;
      clr_vertex->hops = -1;

    }
  }

  /// 根据起点邻接表初始化队列

  queue_init(&queue, NULL);

  if (graph_adjlist(graph, start, &clr_adjlist) != 0) {

    queue_destroy(&queue);
    return -1;
  }

  if (queue_enqueue(&queue, clr_adjlist) != 0) {

    queue_destroy(&queue);
    return -1;
  }

  /// 执行广度优先搜索

  while (queue_size(&queue) > 0) {

    adjlist = queue_peek(&queue);

    /// 在当前邻接表遍历每个顶点

    for (member = list_head(&adjlist->adjacent); member != NULL; member = list_next(member)) {

      adj_vertex = list_data(member);

      /// 确定下个邻接顶点的颜色

      if (graph_adjlist(graph, adj_vertex, &clr_adjlist) != 0) {

        queue_destroy(&queue);
        return -1;
      }

      clr_vertex = clr_adjlist->vertex;

      /// 将白顶点着色为灰色并将邻接表入队

      if (clr_vertex->color == white) {

        clr_vertex->color = gray;
        clr_vertex->hops = ((BfsVertex *)adjlist->vertex)->hops + 1;

        if (queue_enqueue(&queue, clr_adjlist) != 0) {

          queue_destroy(&queue);
          return -1;
        }
      }
    }

    /// 将当前邻接表出队并将其着色为黑色

    if (queue_dequeue(&queue, (void **)&adjlist) == 0) {

      ((BfsVertex *)adjlist->vertex)->color = black;

    } else {

      queue_destroy(&queue);
      return -1;
    }
  }

  queue_destroy(&queue);

  /// 回传每个顶点的跳数到表中

  list_init(hops, NULL);

  for (element = list_head(&graph_adjlists(graph)); element != NULL; element = list_next(element)) {

    /// 去掉跳数为 -1 的（不可达）

    clr_vertex = ((AdjList *)list_data(element))->vertex;
    
    if (clr_vertex->hops != -1) {
      
      if (list_ins_next(hops, list_tail(hops), clr_vertex) != 0) {
        
        list_destroy(hops);
        return -1;
      }
    }
  }
  
  return 0;
}

