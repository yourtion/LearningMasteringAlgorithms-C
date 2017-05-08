//
//  graph.c
//  Algorithms - Graph
//
//  Created by YourtionGuo on 08/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "list.h"
#include "set.h"

#pragma mark - Public

void graph_init(Graph *graph,
                int (*match)(const void *key1, const void *key2),
                void (*destroy)(void *data))
{
  /// 初始化图
  graph->vcount = 0;
  graph->ecount = 0;
  graph->match = match;
  graph->destroy = destroy;

  /// 初始化邻接表结构
  list_init(&graph->adjlists, NULL);

  return;
}


void graph_destroy(Graph *graph)
{
  AdjList     *adjlist;

  /// 销毁每个邻接表
  while (list_size(&graph->adjlists) > 0) {

    if (list_rem_next(&graph->adjlists, NULL, (void **)&adjlist) == 0) {

      set_destroy(&adjlist->adjacent);

      if (graph->destroy != NULL) graph->destroy(adjlist->vertex);

      free(adjlist);

    }
  }

  /// 销毁邻接表结构
  list_destroy(&graph->adjlists);

  /// 清理图数据结构
  memset(graph, 0, sizeof(Graph));

  return;
}


int graph_ins_vertex(Graph *graph, const void *data)
{
  ListElmt  *element;
  AdjList   *adjlist;
  int       retval;

  /// 不允许插入重复的顶点
  for (element = list_head(&graph->adjlists); element != NULL; element = list_next(element)) {

    if (graph->match(data, ((AdjList *)list_data(element))->vertex)) return 1;
  }

  /// 插入顶点

  if ((adjlist = (AdjList *)malloc(sizeof(AdjList))) == NULL) return -1;

  adjlist->vertex = (void *)data;
  set_init(&adjlist->adjacent, graph->match, graph->destroy);

  if ((retval = list_ins_next(&graph->adjlists, list_tail(&graph->adjlists), adjlist)) != 0) {

    return retval;

  }

  /// 更新顶点数量
  graph->vcount++;

  return 0;
}


int graph_ins_edge(Graph *graph, const void *data1, const void *data2)
{
  ListElmt    *element;
  int       retval;

  /// 不允许插入顶点不在图中的边

  for (element = list_head(&graph->adjlists); element != NULL; element = list_next(element)) {

    if (graph->match(data2, ((AdjList *)list_data(element))->vertex)) break;

  }
  if (element == NULL) return -1;

  for (element = list_head(&graph->adjlists); element != NULL; element = list_next(element)) {

    if (graph->match(data1, ((AdjList *)list_data(element))->vertex)) break;

  }
  if (element == NULL) return -1;

  /// 将顶点2插入到顶点1的邻接表
  if ((retval = set_insert(&((AdjList *)list_data(element))->adjacent, data2)) != 0) return retval;

  /// 更新边数量
  graph->ecount++;

  return 0;
}


int graph_rem_vertex(Graph *graph, void **data)
{
  ListElmt  *element, *temp, *prev;
  AdjList   *adjlist;
  int       found;

  /// 遍历每个邻接表及其包含的顶点
  temp = NULL;
  prev = NULL;
  found = 0;

  for (element = list_head(&graph->adjlists); element != NULL; element = list_next(element)) {

    /// 不允许删除仍存在于邻接表的顶点
    if (set_is_member(&((AdjList *)list_data(element))->adjacent, *data)) return -1;

    /// 保存将被删除顶点的指针
    if (graph->match(*data, ((AdjList *)list_data(element))->vertex)) {

      temp = element;
      found = 1;
    }

    /// 在顶点删除前保持它的指针
    if (!found) prev = element;
  }

  /// 如果顶点不存在返回 -1
  if (!found) return -1;

  /// 不允许删除它的邻接表不为空的顶点
  if (set_size(&((AdjList *)list_data(temp))->adjacent) > 0) return -1;

  /// 删除顶点
  if (list_rem_next(&graph->adjlists, prev, (void **)&adjlist) != 0) return -1;

  /// 销毁之前生成的数据结构
  *data = adjlist->vertex;
  free(adjlist);

  /// 更新顶点数量
  graph->vcount--;

  return 0;
}


int graph_rem_edge(Graph *graph, void *data1, void **data2)
{
  ListElmt    *element;

  /// 找到第一个节点的邻接表
  for (element = list_head(&graph->adjlists); element != NULL; element = list_next(element)) {

    if (graph->match(data1, ((AdjList *)list_data(element))->vertex)) break;

  }

  if (element == NULL) return -1;

  /// 从邻接表中删除存在顶点2的边
  if (set_remove(&((AdjList *)list_data(element))->adjacent, data2) != 0) return -1;

  /// 更新边的数量
  graph->ecount--;

  return 0;
}


int graph_adjlist(const Graph *graph, const void *data, AdjList **adjlist) {

  ListElmt    *element, *prev;

  /// 找到包含该顶点的邻接表
  prev = NULL;

  for (element = list_head(&graph->adjlists); element != NULL; element = list_next(element)) {

    if (graph->match(data, ((AdjList *)list_data(element))->vertex)) break;

    prev = element;
  }

  /// 找不到顶点返回 -1
  if (element == NULL) return -1;

  /// 返回该顶点的邻接表
  *adjlist = list_data(element);

  return 0;
}


int graph_is_adjacent(const Graph *graph, const void *data1, const void *data2)
{
  ListElmt    *element, *prev;

  /// 找到第一个节点的邻接表
  prev = NULL;

  for (element = list_head(&graph->adjlists); element != NULL; element = list_next(element)) {

    if (graph->match(data1, ((AdjList *)list_data(element))->vertex)) break;

    prev = element;
  }
  
  /// 找不到顶点返回 0
  if (element == NULL) return 0;
  
  /// 判断顶点2是否在顶点1的邻接表中
  return set_is_member(&((AdjList *)list_data(element))->adjacent, data2);
}
