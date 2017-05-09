//
//  dfs.c
//  Algorithms - Graph depth-first search
//
//  Created by YourtionGuo on 08/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <stdlib.h>

#include "dfs.h"
#include "graph.h"
#include "list.h"

#pragma mark - Private


/**
 实际执行深度优先搜索

 @param graph 图
 @param adjlist 邻接表
 @param ordered 顶点链表
 @return 成功返回0；否则返回-1
 */
static int dfs_main(Graph *graph, AdjList *adjlist, List *ordered)
{
  AdjList     *clr_adjlist;
  DfsVertex   *clr_vertex, *adj_vertex;
  ListElmt    *member;

  /// 将顶点着色为灰色并遍历它的邻接表

  ((DfsVertex *)adjlist->vertex)->color = gray;

  for (member = list_head(&adjlist->adjacent); member != NULL; member = list_next(member)) {

    /// 确定下一个邻接顶点的颜色

    adj_vertex = list_data(member);

    if (graph_adjlist(graph, adj_vertex, &clr_adjlist) != 0) return -1;

    clr_vertex = clr_adjlist->vertex;

    /// 深入邻接顶点如果为白色

    if (clr_vertex->color == white) {

      if (dfs_main(graph, clr_adjlist, ordered) != 0)return -1;

    }
  }

  /// 将当前顶点着色为黑色并将它放在列表头

  ((DfsVertex *)adjlist->vertex)->color = black;

  if (list_ins_next(ordered, NULL, (DfsVertex *)adjlist->vertex) != 0) return -1;

  return 0;
}

#pragma mark - Public

int dfs(Graph *graph, List *ordered)
{
  DfsVertex   *vertex;
  ListElmt    *element;

  /// 初始化图的所有顶点

  for (element = list_head(&graph_adjlists(graph)); element != NULL; element = list_next(element)) {

    vertex = ((AdjList *)list_data(element))->vertex;
    vertex->color = white;

  }

  /// 执行深度优先搜索

  list_init(ordered, NULL);

  for (element = list_head(&graph_adjlists(graph)); element != NULL; element = list_next(element)) {

    /// 确保每个未连接顶点被搜索到

    vertex = ((AdjList *)list_data(element))->vertex;
    
    if (vertex->color == white) {
      
      if (dfs_main(graph, (AdjList *)list_data(element), ordered) != 0) {
        
        list_destroy(ordered);
        return -1;
      }
    }
  }
  
  return 0;
}
