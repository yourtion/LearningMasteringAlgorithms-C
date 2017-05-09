//
//  main.c
//  MasteringAlgorithms
//  Illustrates depth-first search (see Chapter 11).
//
//  Created by YourtionGuo on 05/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dfs.h"
#include "graph.h"
#include "list.h"
#include "set.h"

/// 定义字符串长度
#define     STRSIZ      11


static void print_graph(const Graph *graph)
{
  Set         *adjacent;
  DfsVertex   *vertex;
  ListElmt    *element, *member;
  int         i, j;

  /// 打印图结构

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
      fprintf(stdout, "%s", (char *)vertex->data);
      member = list_next(member);
      j++;

    }

    i++;
    fprintf(stdout, "\n");
    element = list_next(element);

  }

  return;
}


static void destroy_task(void *task)
{
  /// 清理任务相关空间
  free(((DfsVertex *)task)->data);
  free(task);

  return;
}


static int match_task(const void *task1, const void *task2)
{
  /// 判断任务是否匹配
  return !strcmp(((const DfsVertex *)task1)->data, ((const DfsVertex *)task2)->data);
}


int main(int argc, char **argv)
{
  Graph       graph;
  DfsVertex   *task, task1, *task2;
  List        list;
  ListElmt    *element;
  char        data1[STRSIZ];
  int         i;

  /// 初始化图
  graph_init(&graph, match_task, destroy_task);

  /// 插入一些任务

  if ((task = (DfsVertex *)malloc(sizeof(DfsVertex))) == NULL) return 1;

  if ((task->data = malloc(STRSIZ)) == NULL) return 1;

  strcpy((char *)task->data, "a");
  fprintf(stdout, "Inserting vertex %s\n", (char *)task->data);

  if (graph_ins_vertex(&graph, task) != 0) return 1;

  if ((task = (DfsVertex *)malloc(sizeof(DfsVertex))) == NULL) return 1;

  if ((task->data = malloc(STRSIZ)) == NULL) return 1;

  strcpy((char *)task->data, "b");
  fprintf(stdout, "Inserting vertex %s\n", (char *)task->data);

  if (graph_ins_vertex(&graph, task) != 0) return 1;

  if ((task = (DfsVertex *)malloc(sizeof(DfsVertex))) == NULL) return 1;

  if ((task->data = malloc(STRSIZ)) == NULL) return 1;

  strcpy((char *)task->data, "c");
  fprintf(stdout, "Inserting vertex %s\n", (char *)task->data);

  if (graph_ins_vertex(&graph, task) != 0) return 1;

  if ((task = (DfsVertex *)malloc(sizeof(DfsVertex))) == NULL) return 1;

  if ((task->data = malloc(STRSIZ)) == NULL) return 1;

  strcpy((char *)task->data, "d");
  fprintf(stdout, "Inserting vertex %s\n", (char *)task->data);

  if (graph_ins_vertex(&graph, task) != 0) return 1;

  if ((task = (DfsVertex *)malloc(sizeof(DfsVertex))) == NULL) return 1;

  if ((task->data = malloc(STRSIZ)) == NULL) return 1;

  strcpy((char *)task->data, "e");
  fprintf(stdout, "Inserting vertex %s\n", (char *)task->data);

  if (graph_ins_vertex(&graph, task) != 0) return 1;

  if ((task = (DfsVertex *)malloc(sizeof(DfsVertex))) == NULL) return 1;

  if ((task->data = malloc(STRSIZ)) == NULL) return 1;

  strcpy((char *)task->data, "f");
  fprintf(stdout, "Inserting vertex %s\n", (char *)task->data);

  if (graph_ins_vertex(&graph, task) != 0) return 1;

  if ((task = (DfsVertex *)malloc(sizeof(DfsVertex))) == NULL) return 1;

  if ((task->data = malloc(STRSIZ)) == NULL) return 1;

  strcpy((char *)task->data, "g");
  fprintf(stdout, "Inserting vertex %s\n", (char *)task->data);

  if (graph_ins_vertex(&graph, task) != 0) return 1;

  if ((task = (DfsVertex *)malloc(sizeof(DfsVertex))) == NULL) return 1;

  if ((task->data = malloc(STRSIZ)) == NULL) return 1;

  strcpy((char *)task->data, "h");
  fprintf(stdout, "Inserting vertex %s\n", (char *)task->data);

  if (graph_ins_vertex(&graph, task) != 0) return 1;

  if ((task = (DfsVertex *)malloc(sizeof(DfsVertex))) == NULL) return 1;

  if ((task->data = malloc(STRSIZ)) == NULL) return 1;

  strcpy((char *)task->data, "i");
  fprintf(stdout, "Inserting vertex %s\n", (char *)task->data);

  if (graph_ins_vertex(&graph, task) != 0) return 1;

  print_graph(&graph);

  /// 插入任务依赖关系

  task1.data = data1;

  if ((task2 = (DfsVertex *)malloc(sizeof(DfsVertex))) == NULL) return 1;

  if ((task2->data = malloc(STRSIZ)) == NULL) return 1;

  strcpy((char *)task1.data, "a");
  strcpy((char *)task2->data, "b");
  fprintf(stdout, "Inserting edge %s to %s\n", (char *)task1.data, (char *)task2->data);

  if (graph_ins_edge(&graph, &task1, task2) != 0) return 1;

  print_graph(&graph);

  if ((task2 = (DfsVertex *)malloc(sizeof(DfsVertex))) == NULL) return 1;

  if ((task2->data = malloc(STRSIZ)) == NULL) return 1;

  strcpy((char *)task1.data, "a");
  strcpy((char *)task2->data, "c");
  fprintf(stdout, "Inserting edge %s to %s\n", (char *)task1.data, (char *)task2->data);

  if (graph_ins_edge(&graph, &task1, task2) != 0) return 1;

  print_graph(&graph);

  if ((task2 = (DfsVertex *)malloc(sizeof(DfsVertex))) == NULL) return 1;

  if ((task2->data = malloc(STRSIZ)) == NULL) return 1;

  strcpy((char *)task1.data, "b");
  strcpy((char *)task2->data, "i");
  fprintf(stdout, "Inserting edge %s to %s\n", (char *)task1.data, (char *)task2->data);

  if (graph_ins_edge(&graph, &task1, task2) != 0) return 1;

  print_graph(&graph);

  if ((task2 = (DfsVertex *)malloc(sizeof(DfsVertex))) == NULL) return 1;

  if ((task2->data = malloc(STRSIZ)) == NULL) return 1;

  strcpy((char *)task1.data, "c");
  strcpy((char *)task2->data, "i");
  fprintf(stdout, "Inserting edge %s to %s\n", (char *)task1.data, (char *)task2->data);

  if (graph_ins_edge(&graph, &task1, task2) != 0) return 1;

  print_graph(&graph);

  if ((task2 = (DfsVertex *)malloc(sizeof(DfsVertex))) == NULL) return 1;

  if ((task2->data = malloc(STRSIZ)) == NULL) return 1;

  strcpy((char *)task1.data, "e");
  strcpy((char *)task2->data, "f");
  fprintf(stdout, "Inserting edge %s to %s\n", (char *)task1.data, (char *)task2->data);

  if (graph_ins_edge(&graph, &task1, task2) != 0) return 1;

  print_graph(&graph);

  if ((task2 = (DfsVertex *)malloc(sizeof(DfsVertex))) == NULL) return 1;

  if ((task2->data = malloc(STRSIZ)) == NULL) return 1;

  strcpy((char *)task1.data, "e");
  strcpy((char *)task2->data, "h");
  fprintf(stdout, "Inserting edge %s to %s\n", (char *)task1.data, (char *)task2->data);

  if (graph_ins_edge(&graph, &task1, task2) != 0) return 1;

  print_graph(&graph);

  if ((task2 = (DfsVertex *)malloc(sizeof(DfsVertex))) == NULL) return 1;

  if ((task2->data = malloc(STRSIZ)) == NULL) return 1;

  strcpy((char *)task1.data, "f");
  strcpy((char *)task2->data, "c");
  fprintf(stdout, "Inserting edge %s to %s\n", (char *)task1.data, (char *)task2->data);

  if (graph_ins_edge(&graph, &task1, task2) != 0) return 1;

  print_graph(&graph);

  if ((task2 = (DfsVertex *)malloc(sizeof(DfsVertex))) == NULL) return 1;

  if ((task2->data = malloc(STRSIZ)) == NULL) return 1;

  strcpy((char *)task1.data, "f");
  strcpy((char *)task2->data, "h");
  fprintf(stdout, "Inserting edge %s to %s\n", (char *)task1.data, (char *)task2->data);

  if (graph_ins_edge(&graph, &task1, task2) != 0) return 1;

  print_graph(&graph);

  if ((task2 = (DfsVertex *)malloc(sizeof(DfsVertex))) == NULL) return 1;

  if ((task2->data = malloc(STRSIZ)) == NULL) return 1;

  strcpy((char *)task1.data, "g");
  strcpy((char *)task2->data, "h");
  fprintf(stdout, "Inserting edge %s to %s\n", (char *)task1.data, (char *)task2->data);

  if (graph_ins_edge(&graph, &task1, task2) != 0)return 1;

  print_graph(&graph);

  /// 执行深度优先搜索

  fprintf(stdout, "Generating the depth-first search listing\n");

  if (dfs(&graph, &list) != 0) return 1;

  i = 0;

  for (element = list_head(&list); element != NULL; element = list_next(element)) {

    task = list_data(element);
    fprintf(stdout, "list[%03d]=%s (color=%d)\n", i, (char *)task->data, task->color);
    i++;
  }

  /// 销毁链表
  fprintf(stdout, "Destroying the list\n");
  list_destroy(&list);
  
  /// 销毁图
  fprintf(stdout, "Destroying the graph\n");
  graph_destroy(&graph);
  
  return 0;
}
