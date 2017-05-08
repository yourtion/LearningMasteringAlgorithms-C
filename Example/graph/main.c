//
//  main.c
//  MasteringAlgorithms
//  Illustrates using a graph (see Chapter 11).
//
//  Created by YourtionGuo on 08/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "list.h"
#include "set.h"

/// 定义字符串长度
#define     STRSIZ      2


static void print_graph(const Graph *graph)
{
  Set       *adjacent;
  ListElmt  *element, *member;
  int       i, j;

  /// 打印图结构
  fprintf(stdout, "-> Vertices=%d, edges=%d\n", graph_vcount(graph), graph_ecount(graph));

  i = 0;
  element = list_head(&graph_adjlists(graph));

  while (i < list_size(&graph_adjlists(graph))) {

    fprintf(stdout, "--> graph[%03d]=%s: ", i, (char *)((AdjList *)list_data(element))->vertex);

    j = 0;
    adjacent = &((AdjList *)list_data(element))->adjacent;
    member = list_head(adjacent);

    while (j < set_size(adjacent)) {

      if (j > 0) fprintf(stdout, ", ");
      fprintf(stdout, "%s", (char *)list_data(member));
      member = list_next(member);
      j++;

    }

    i++;
    fprintf(stdout, "\n");
    element = list_next(element);

  }

  return;
}


static int match_str(const void *str1, const void *str2)
{
  /// 字符串对比函数
  return !strcmp((const char *)str1, (const char *)str2);
}


int main(int argc, char **argv)
{
  Graph     graph;
  AdjList   *adjlist;
  ListElmt  *element;
  char      *data, data1[STRSIZ], *data2;
  int       retval, size, i;

  /// 初始化图
  graph_init(&graph, match_str, free);

  /// 执行图操作
  if ((data = (char *)malloc(STRSIZ)) == NULL) return 1;

  strcpy(data, "a");
  fprintf(stdout, "Inserting vertex %s\n", data);

  if (graph_ins_vertex(&graph, data) != 0) return 1;

  if ((data = (char *)malloc(STRSIZ)) == NULL) return 1;

  strcpy(data, "b");
  fprintf(stdout, "Inserting vertex %s\n", data);

  if (graph_ins_vertex(&graph, data) != 0) return 1;

  if ((data = (char *)malloc(STRSIZ)) == NULL) return 1;

  strcpy(data, "c");
  fprintf(stdout, "Inserting vertex %s\n", data);

  if (graph_ins_vertex(&graph, data) != 0) return 1;

  if ((data = (char *)malloc(STRSIZ)) == NULL) return 1;

  strcpy(data, "d");
  fprintf(stdout, "Inserting vertex %s\n", data);

  if (graph_ins_vertex(&graph, data) != 0) return 1;

  if ((data = (char *)malloc(STRSIZ)) == NULL) return 1;

  strcpy(data, "e");
  fprintf(stdout, "Inserting vertex %s\n", data);

  if (graph_ins_vertex(&graph, data) != 0) return 1;

  print_graph(&graph);

  if ((data2 = (char *)malloc(STRSIZ)) == NULL) return 1;

  strcpy(data1, "a");
  strcpy(data2, "b");
  fprintf(stdout, "Inserting edge %s to %s\n", data1, data2);

  if (graph_ins_edge(&graph, data1, data2) != 0) return 1;

  print_graph(&graph);

  if ((data2 = (char *)malloc(STRSIZ)) == NULL) return 1;

  strcpy(data1, "a");
  strcpy(data2, "c");
  fprintf(stdout, "Inserting edge %s to %s\n", data1, data2);

  if (graph_ins_edge(&graph, data1, data2) != 0) return 1;

  print_graph(&graph);

  if ((data2 = (char *)malloc(STRSIZ)) == NULL) return 1;

  strcpy(data1, "b");
  strcpy(data2, "c");
  fprintf(stdout, "Inserting edge %s to %s\n", data1, data2);

  if (graph_ins_edge(&graph, data1, data2) != 0) return 1;

  print_graph(&graph);

  if ((data2 = (char *)malloc(STRSIZ)) == NULL) return 1;

  strcpy(data1, "b");
  strcpy(data2, "d");
  fprintf(stdout, "Inserting edge %s to %s\n", data1, data2);

  if (graph_ins_edge(&graph, data1, data2) != 0) return 1;

  print_graph(&graph);

  if ((data2 = (char *)malloc(STRSIZ)) == NULL) return 1;

  strcpy(data1, "c");
  strcpy(data2, "b");
  fprintf(stdout, "Inserting edge %s to %s\n", data1, data2);

  if (graph_ins_edge(&graph, data1, data2) != 0) return 1;

  print_graph(&graph);

  if ((data2 = (char *)malloc(STRSIZ)) == NULL) return 1;

  strcpy(data1, "c");
  strcpy(data2, "c");
  fprintf(stdout, "Inserting edge %s to %s\n", data1, data2);

  if (graph_ins_edge(&graph, data1, data2) != 0) return 1;

  print_graph(&graph);

  if ((data2 = (char *)malloc(STRSIZ)) == NULL) return 1;

  strcpy(data1, "c");
  strcpy(data2, "d");
  fprintf(stdout, "Inserting edge %s to %s\n", data1, data2);

  if (graph_ins_edge(&graph, data1, data2) != 0) return 1;

  print_graph(&graph);

  if ((data2 = (char *)malloc(STRSIZ)) == NULL) return 1;

  strcpy(data1, "d");
  strcpy(data2, "a");
  fprintf(stdout, "Inserting edge %s to %s\n", data1, data2);

  if (graph_ins_edge(&graph, data1, data2) != 0) return 1;

  print_graph(&graph);

  if ((data2 = (char *)malloc(STRSIZ)) == NULL) return 1;

  strcpy(data1, "e");
  strcpy(data2, "c");
  fprintf(stdout, "Inserting edge %s to %s\n", data1, data2);

  if (graph_ins_edge(&graph, data1, data2) != 0) return 1;

  print_graph(&graph);

  if ((data2 = (char *)malloc(STRSIZ)) == NULL) return 1;

  strcpy(data1, "e");
  strcpy(data2, "d");
  fprintf(stdout, "Inserting edge %s to %s\n", data1, data2);

  if (graph_ins_edge(&graph, data1, data2) != 0) return 1;

  print_graph(&graph);

  if ((data2 = (char *)malloc(STRSIZ)) == NULL) return 1;

  strcpy(data1, "a");
  strcpy(data2, "c");
  data = data2;

  fprintf(stdout, "Removing edge %s to %s\n", data1, data2);

  if (graph_rem_edge(&graph, data1, (void **)&data) != 0) return 1;

  free(data);
  print_graph(&graph);

  strcpy(data1, "c");
  strcpy(data2, "c");
  data = data2;

  fprintf(stdout, "Removing edge %s to %s\n", data1, data2);

  if (graph_rem_edge(&graph, data1, (void **)&data) != 0) return 1;

  free(data);
  print_graph(&graph);

  strcpy(data1, "e");
  strcpy(data2, "c");
  data = data2;

  fprintf(stdout, "Removing edge %s to %s\n", data1, data2);

  if (graph_rem_edge(&graph, data1, (void **)&data) != 0) return 1;

  free(data);
  print_graph(&graph);

  strcpy(data1, "a");
  strcpy(data2, "b");
  data = data2;

  fprintf(stdout, "Removing edge %s to %s\n", data1, data2);

  if (graph_rem_edge(&graph, data1, (void **)&data) != 0) return 1;

  free(data);
  print_graph(&graph);

  strcpy(data1, "d");
  strcpy(data2, "a");
  data = data2;

  fprintf(stdout, "Removing edge %s to %s\n", data1, data2);

  if (graph_rem_edge(&graph, data1, (void **)&data) != 0) return 1;

  free(data);
  print_graph(&graph);

  free(data2);

  strcpy(data1, "a");
  data = data1;

  fprintf(stdout, "Removing vertex %s\n", data1);

  if (graph_rem_vertex(&graph, (void **)&data) != 0) return 1;

  free(data);
  print_graph(&graph);

  if ((data2 = (char *)malloc(STRSIZ)) == NULL) return 1;

  strcpy(data1, "f");
  strcpy(data2, "a");

  retval = graph_ins_edge(&graph, data1, data2);
  fprintf(stdout,"Inserting an invalid edge from %s to %s...Value=%d (-1=OK)\n",
          data1, data2, retval);

  if (retval != 0) free(data2);

  print_graph(&graph);

  if ((data2 = (char *)malloc(STRSIZ)) == NULL) return 1;

  strcpy(data1, "c");
  strcpy(data2, "b");

  retval = graph_ins_edge(&graph, data1, data2);
  fprintf(stdout,"Inserting an existing edge from %s to %s...Value=%d (1=OK)\n",
          data1, data2, retval);

  if (retval != 0) free(data2);

  print_graph(&graph);

  if ((data2 = (char *)malloc(STRSIZ)) == NULL) return 1;

  strcpy(data1, "f");
  strcpy(data2, "a");
  data = data2;

  retval = graph_rem_edge(&graph, data1, (void **)&data);
  fprintf(stdout, "Removing an invalid edge from %s to %s...Value=%d (-1=OK)\n",
          data1, data2, retval);

  if (retval == 0) free(data);

  free(data2);
  print_graph(&graph);

  if ((data2 = (char *)malloc(STRSIZ)) == NULL) return 1;

  strcpy(data1, "c");
  strcpy(data2, "e");
  data = data2;

  retval = graph_rem_edge(&graph, data1, (void **)&data);
  fprintf(stdout, "Removing an invalid edge from %s to %s...Value=%d (-1=OK)\n",
          data1, data2, retval);

  if (retval == 0) free(data);

  free(data2);
  print_graph(&graph);

  if ((data2 = (char *)malloc(STRSIZ)) == NULL) return 1;

  strcpy(data2, "c");

  retval = graph_ins_vertex(&graph, data2);
  fprintf(stdout, "Inserting an existing vertex %s...Value=%d (1=OK)\n", data1,
          retval);

  if (retval != 0) free(data2);

  print_graph(&graph);

  if ((data2 = (char *)malloc(STRSIZ)) == NULL) return 1;

  strcpy(data1, "b");
  strcpy(data2, "d");

  retval = graph_is_adjacent(&graph, data1, data2);
  fprintf(stdout, "Testing graph_is_adjacent (%s, %s)...Value=%d (1=OK)\n",
          data1, data2, retval);

  strcpy(data1, "a");
  strcpy(data2, "e");

  retval = graph_is_adjacent(&graph, data1, data2);
  fprintf(stdout, "Testing graph_is_adjacent (%s, %s)...Value=%d (0=OK)\n",
          data1, data2, retval);

  strcpy(data1, "e");
  strcpy(data2, "d");

  retval = graph_is_adjacent(&graph, data1, data2);
  fprintf(stdout, "Testing graph_is_adjacent (%s, %s)...Value=%d (1=OK)\n",
          data1, data2, retval);

  strcpy(data1, "c");
  strcpy(data2, "a");

  retval = graph_is_adjacent(&graph, data1, data2);
  fprintf(stdout, "Testing graph_is_adjacent (%s, %s)...Value=%d (0=OK)\n",
          data1, data2, retval);

  free(data2);

  strcpy(data1, "c");
  
  if (graph_adjlist(&graph, data1, &adjlist) != 0) return 1;
  
  fprintf(stdout, "Vertices adjacent to %s: ", data1);
  
  i = 0;
  size = set_size(&adjlist->adjacent);
  element = list_head(&adjlist->adjacent);
  
  while (i < size) {
    
    i++;
    if (i > 1) fprintf(stdout, ", ");
    fprintf(stdout, "%s", (char *)list_data(element));
    element = list_next(element);
    
  }
  
  fprintf(stdout, "\n");

  /// 销毁图数据结构
  fprintf(stdout, "Destroying the graph\n");
  graph_destroy(&graph);
  
  return 0;
}
