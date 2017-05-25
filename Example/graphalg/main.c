//
//  main.c
//  MasteringAlgorithms
//  Illustrates graph algorithms (see Chapter 16).
//
//  Created by YourtionGuo on 23/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "graphalg.h"
#include "list.h"
#include "set.h"

/// 定义字符串长度
#define     STRSIZ      2

/**
 边数据结构
 */
typedef struct EdgeData_
{
  char      vertex1[STRSIZ], vertex2[STRSIZ];
  double    weight;

} EdgeData;

/**
 坐标数据结构
 */
typedef struct CoordData_
{
  char      vertex[STRSIZ];
  double    x, y;

} CoordData;

/// 定义最小生成树计算数据

#define     MSTVCT      9
#define     MSTECT      28

static char MstTestV[MSTVCT][STRSIZ] = { "a", "b", "c", "d", "e", "f", "g", "h", "i" };

static EdgeData MstTestE[MSTECT] =
{
  {"a", "b", 4.0},
  {"a", "h", 8.0},
  {"b", "a", 4.0},
  {"b", "c", 8.0},
  {"b", "h", 11.0},
  {"c", "b", 8.0},
  {"c", "d", 7.0},
  {"c", "f", 4.0},
  {"c", "i", 2.0},
  {"d", "c", 7.0},
  {"d", "e", 9.0},
  {"d", "f", 14.0},
  {"e", "d", 9.0},
  {"e", "f", 10.0},
  {"f", "c", 4.0},
  {"f", "d", 14.0},
  {"f", "e", 10.0},
  {"f", "g", 2.0},
  {"g", "f", 2.0},
  {"g", "h", 1.0},
  {"g", "i", 6.0},
  {"h", "a", 8.0},
  {"h", "b", 11.0},
  {"h", "g", 1.0},
  {"h", "i", 7.0},
  {"i", "c", 2.0},
  {"i", "g", 6.0},
  {"i", "h", 7.0}
};

/// 定义最短边计算数据

#define     PTHVCT      6
#define     PTHECT      11

static char PthTestV[PTHVCT][STRSIZ] = { "a", "b", "c", "d", "e", "f" };

static EdgeData PthTestE[PTHECT] =
{
  {"a", "b", 8.0},
  {"a", "c", 4.0},
  {"b", "c", 6.0},
  {"b", "d", 2.0},
  {"b", "f", 4.0},
  {"c", "e", 4.0},
  {"c", "f", 1.0},
  {"e", "f", 5.0},
  {"f", "b", 2.0},
  {"f", "d", 7.0},
  {"f", "e", 4.0}
};

/// 定义旅行商问题数据

#define     TSPVCT      7

static CoordData TspTestV[TSPVCT] =
{
  {"a", 2.0, 1.0},
  {"b", 1.0, 3.0},
  {"c", 2.0, 4.0},
  {"d", 4.0, 3.0},
  {"e", 5.0, 2.0},
  {"f", 5.0, 5.0},
  {"g", 6.0, 3.0}
};

static void print_graph_mst(const Graph *graph)
{
  Set         *adjacent;
  MstVertex   *vertex;
  ListElmt    *element, *member;
  int         i, j;

  /// 打印最小生成树的图

  fprintf(stdout, "-> Vertices=%d, edges=%d\n", graph_vcount(graph), graph_ecount(graph));

  i = 0;
  element = list_head(&graph_adjlists(graph));

  while (i < list_size(&graph_adjlists(graph))) {

    vertex = ((AdjList *)list_data(element))->vertex;
    fprintf(stdout, "--> graph[%03d]=%s: ", i, (char *)vertex->data);

    j = 0;
    adjacent = &((AdjList *)list_data(element))->adjacent;
    member = list_head(adjacent);

    while (j < set_size(adjacent)) {

      vertex = list_data(member);
      if (j > 0) fprintf(stdout, ", ");
      fprintf(stdout, "%s(%4.1lf)", (char *)vertex->data, vertex->weight);
      member = list_next(member);
      j++;

    }

    i++;
    fprintf(stdout, "\n");
    element = list_next(element);
  }

  return;
}

static int match_mst(const void *mst1, const void *mst2)
{
  /// 确定两个 MstVertex 顶点是否相等
  return !strcmp(((const MstVertex *)mst1)->data, ((const MstVertex *)mst2)->data);
}


static void print_graph_pth(const Graph *graph)
{
  Set           *adjacent;
  PathVertex    *vertex;
  ListElmt      *element, *member;
  int           i, j;

  /// 打印最短边计算的图

  fprintf(stdout, "-> Vertices=%d, edges=%d\n", graph_vcount(graph), graph_ecount(graph));

  i = 0;
  element = list_head(&graph_adjlists(graph));

  while (i < list_size(&graph_adjlists(graph))) {

    vertex = ((AdjList *)list_data(element))->vertex;
    fprintf(stdout, "--> graph[%03d]=%s: ", i, (char *)vertex->data);

    j = 0;
    adjacent = &((AdjList *)list_data(element))->adjacent;
    member = list_head(adjacent);

    while (j < set_size(adjacent)) {

      vertex = list_data(member);
      if (j > 0) fprintf(stdout, ", ");
      fprintf(stdout, "%s(%4.1lf)", (char *)vertex->data, vertex->weight);
      member = list_next(member);
      j++;

    }

    i++;
    fprintf(stdout, "\n");
    element = list_next(element);

  }

  return;
}

static int match_pth(const void *pth1, const void *pth2)
{
  /// 确定两个 PathVertex 顶点是否相等
  return !strcmp(((const PathVertex *)pth1)->data, ((const PathVertex *)pth2)->data);
}

static void print_list_tsp(List *vertices)
{
  TspVertex   *vertex;
  ListElmt    *element;
  int         i;

  /// 打印旅行商问题列表顶点

  fprintf(stdout, "-> Vertices=%d\n", list_size(vertices));

  i = 0;
  element = list_head(vertices);

  while (1) {

    vertex = list_data(element);
    fprintf(stdout, "--> vertices[%03d]=%s: (%.1lf, %.1lf)\n", i, (char *)vertex->data, vertex->x, vertex->y);

    i++;

    if (list_is_tail(element)) {
      break;
    } else {
      element = list_next(element);
    }
  }

  return;
}

static int match_tsp(const void *tsp1, const void *tsp2)
{
  /// 确定两个 TspVertex 顶点是否相等
  return !strcmp(((const TspVertex *)tsp1)->data, ((const TspVertex *)tsp2)->data);
}


int main(int argc, char **argv)
{

  Graph       graph;
  MstVertex   *mst_start, *mst_vertex, mst_vertex1, *mst_vertex2;
  PathVertex  *pth_start, *pth_vertex, pth_vertex1, *pth_vertex2;
  TspVertex   *tsp_start, *tsp_vertex;
  List        span, paths, vertices, tour;
  ListElmt    *element;
  double      distance = 0.0, total, x = 0.0, y = 0.0;
  int         i;

  /// 计算最小生成树

  graph_init(&graph, match_mst, free);

  fprintf(stdout, "Computing a minimum spanning tree\n");

  for (i = 0; i < MSTVCT; i++) {

    if ((mst_vertex = (MstVertex *)malloc(sizeof(MstVertex))) == NULL) return 1;

    if (i == 0) {
      mst_start = mst_vertex;
    }

    mst_vertex->data = MstTestV[i];

    if (graph_ins_vertex(&graph, mst_vertex) != 0) return 1;
  }

  for (i = 0; i < MSTECT; i++) {

    if ((mst_vertex2 = (MstVertex *)malloc(sizeof(MstVertex))) == NULL) return 1;

    mst_vertex1.data = MstTestE[i].vertex1;
    mst_vertex2->data = MstTestE[i].vertex2;
    mst_vertex2->weight = MstTestE[i].weight;

    if (graph_ins_edge(&graph, &mst_vertex1, mst_vertex2) != 0) return 1;

  }

  print_graph_mst(&graph);

  if (mst(&graph, mst_start, &span, match_mst) != 0) return 1;

  for (element = list_head(&span); element != NULL; element = list_next(element)) {

    mst_vertex = list_data(element);

    fprintf(stdout, "vertex=%s, parent=%s\n", (char *)mst_vertex->data,
            mst_vertex->parent != NULL ? (char *)mst_vertex->parent->data : "*");
    
  }

  list_destroy(&span);
  graph_destroy(&graph);

  /// 计算最短路径

  graph_init(&graph, match_pth, free);

  fprintf(stdout, "Computing shortest paths\n");

  for (i = 0; i < PTHVCT; i++) {

    if ((pth_vertex = (PathVertex *)malloc(sizeof(PathVertex))) == NULL) return 1;

    if (i == 1) {
      pth_start = pth_vertex;
    }

    pth_vertex->data = PthTestV[i];

    if (graph_ins_vertex(&graph, pth_vertex) != 0) return 1;

  }

  for (i = 0; i < PTHECT; i++) {

    if ((pth_vertex2 = (PathVertex *)malloc(sizeof(PathVertex))) == NULL) return 1;

    pth_vertex1.data = PthTestE[i].vertex1;
    pth_vertex2->data = PthTestE[i].vertex2;
    pth_vertex2->weight = PthTestE[i].weight;

    if (graph_ins_edge(&graph, &pth_vertex1, pth_vertex2) != 0) return 1;
  }

  print_graph_pth(&graph);

  if (shortest(&graph, pth_start, &paths, match_pth) != 0) return 1;

  for (element = list_head(&paths); element != NULL; element = list_next(element)) {

    pth_vertex = list_data(element);

    fprintf(stdout, "vertex=%s, parent=%s, d=%.1lf\n",
            (char *)pth_vertex->data,
            pth_vertex->parent != NULL ? (char *)pth_vertex->parent->data :"*",
            pth_vertex->d);
    
  }
  
  list_destroy(&paths);
  graph_destroy(&graph);

  /// 解决旅行商问题

  list_init(&vertices, free);

  fprintf(stdout, "Solving a traveling-salesman problem\n");

  for (i = 0; i < TSPVCT; i++) {

    if ((tsp_vertex = (TspVertex *)malloc(sizeof(TspVertex))) == NULL) return 1;

    if (i == 0) {
      tsp_start = tsp_vertex;
    }

    tsp_vertex->data = TspTestV[i].vertex;
    tsp_vertex->x = TspTestV[i].x;
    tsp_vertex->y = TspTestV[i].y;

    if (list_ins_next(&vertices, list_tail(&vertices), tsp_vertex) != 0) return 1;

  }

  print_list_tsp(&vertices);

  if (tsp(&vertices, tsp_start, &tour, match_tsp) != 0) return 1;

  total = 0;

  for (element = list_head(&tour); element != NULL; element = list_next(element)) {

    tsp_vertex = list_data(element);

    if (!list_is_head(&tour, element)) {

      distance = sqrt(pow(tsp_vertex->x-x, 2.0) + pow(tsp_vertex->y-y, 2.0));
      total = total + distance;

    }

    x = tsp_vertex->x;
    y = tsp_vertex->y;

    if (!list_is_head(&tour, element)) {
      fprintf(stdout, "vertex=%s, distance=%.2lf\n", (char *)tsp_vertex->data, distance);
    } else {
      fprintf(stdout, "vertex=%s\n", (char *)tsp_vertex->data);
    }

  }
  
  fprintf(stdout, "total=%.2lf\n", total);
  
  list_destroy(&vertices);
  list_destroy(&tour);

  return 0;
}
