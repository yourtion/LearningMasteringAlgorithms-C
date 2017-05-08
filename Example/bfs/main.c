//
//  main.c
//  MasteringAlgorithms
//  Illustrates breadth-first search (see Chapter 11).
//
//  Created by YourtionGuo on 05/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bfs.h"
#include "graph.h"
#include "list.h"
#include "set.h"

/// 定义字符串长度
#define     STRSIZ      2


static void print_graph(const Graph *graph)
{
  Set         *adjacent;
  BfsVertex   *vertex;
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


static void destroy_netid(void *netid)
{
  /// 清理网络ID相关空间
  free(((BfsVertex *)netid)->data);
  free(netid);

  return;
}


static int match_netid(const void *netid1, const void *netid2)
{
  /// 判断网络ID是否匹配
  return !strcmp(((const BfsVertex *)netid1)->data, ((const BfsVertex *)netid2)->data);
}

int main(int argc, char **argv)
{

  Graph       network;
  BfsVertex   *netid, netid1, *netid2;
  List        list;
  ListElmt    *element;
  char        data1[STRSIZ];
  int         i;

  /// 初始化图

  graph_init(&network, match_netid, destroy_netid);

  /// 插入网络ID

  if ((netid = (BfsVertex *)malloc(sizeof(BfsVertex))) == NULL) return 1;

  if ((netid->data = malloc(STRSIZ)) == NULL) return 1;

  strcpy((char *)netid->data, "node1");
  fprintf(stdout, "Inserting vertex %s\n", (char *)netid->data);

  if (graph_ins_vertex(&network, netid) != 0) return 1;

  if ((netid = (BfsVertex *)malloc(sizeof(BfsVertex))) == NULL) return 1;

  if ((netid->data = malloc(STRSIZ)) == NULL) return 1;

  strcpy((char *)netid->data, "node2");
  fprintf(stdout, "Inserting vertex %s\n", (char *)netid->data);

  if (graph_ins_vertex(&network, netid) != 0) return 1;

  if ((netid = (BfsVertex *)malloc(sizeof(BfsVertex))) == NULL) return 1;

  if ((netid->data = malloc(STRSIZ)) == NULL) return 1;

  strcpy((char *)netid->data, "node3");
  fprintf(stdout, "Inserting vertex %s\n", (char *)netid->data);

  if (graph_ins_vertex(&network, netid) != 0) return 1;

  if ((netid = (BfsVertex *)malloc(sizeof(BfsVertex))) == NULL) return 1;

  if ((netid->data = malloc(STRSIZ)) == NULL) return 1;

  strcpy((char *)netid->data, "node4");
  fprintf(stdout, "Inserting vertex %s\n", (char *)netid->data);

  if (graph_ins_vertex(&network, netid) != 0) return 1;

  if ((netid = (BfsVertex *)malloc(sizeof(BfsVertex))) == NULL) return 1;

  if ((netid->data = malloc(STRSIZ)) == NULL) return 1;

  strcpy((char *)netid->data, "node5");
  fprintf(stdout, "Inserting vertex %s\n", (char *)netid->data);

  if (graph_ins_vertex(&network, netid) != 0) return 1;

  if ((netid = (BfsVertex *)malloc(sizeof(BfsVertex))) == NULL) return 1;

  if ((netid->data = malloc(STRSIZ)) == NULL) return 1;

  strcpy((char *)netid->data, "node6");
  fprintf(stdout, "Inserting vertex %s\n", (char *)netid->data);

  if (graph_ins_vertex(&network, netid) != 0) return 1;

  print_graph(&network);

  /// 加入一些网络连接

  netid1.data = data1;

  if ((netid2 = (BfsVertex *)malloc(sizeof(BfsVertex))) == NULL) return 1;

  if ((netid2->data = malloc(STRSIZ)) == NULL) return 1;

  strcpy((char *)netid1.data, "node1");
  strcpy((char *)netid2->data, "node2");
  fprintf(stdout, "Inserting edge %s to %s\n", (char *)netid1.data, (char *)netid2->data);

  if (graph_ins_edge(&network, &netid1, netid2) != 0) return 1;

  print_graph(&network);

  if ((netid2 = (BfsVertex *)malloc(sizeof(BfsVertex))) == NULL) return 1;

  if ((netid2->data = malloc(STRSIZ)) == NULL) return 1;

  strcpy((char *)netid1.data, "node2");
  strcpy((char *)netid2->data, "node1");
  fprintf(stdout, "Inserting edge %s to %s\n", (char *)netid1.data, (char *)netid2->data);

  if (graph_ins_edge(&network, &netid1, netid2) != 0) return 1;

  print_graph(&network);

  if ((netid2 = (BfsVertex *)malloc(sizeof(BfsVertex))) == NULL) return 1;

  if ((netid2->data = malloc(STRSIZ)) == NULL) return 1;

  strcpy((char *)netid1.data, "node1");
  strcpy((char *)netid2->data, "node3");
  fprintf(stdout, "Inserting edge %s to %s\n", (char *)netid1.data, (char *)netid2->data);

  if (graph_ins_edge(&network, &netid1, netid2) != 0) return 1;

  print_graph(&network);

  if ((netid2 = (BfsVertex *)malloc(sizeof(BfsVertex))) == NULL) return 1;

  if ((netid2->data = malloc(STRSIZ)) == NULL) return 1;

  strcpy((char *)netid1.data, "node3");
  strcpy((char *)netid2->data, "node1");
  fprintf(stdout, "Inserting edge %s to %s\n", (char *)netid1.data, (char *)netid2->data);

  if (graph_ins_edge(&network, &netid1, netid2) != 0) return 1;

  print_graph(&network);

  if ((netid2 = (BfsVertex *)malloc(sizeof(BfsVertex))) == NULL) return 1;

  if ((netid2->data = malloc(STRSIZ)) == NULL) return 1;

  strcpy((char *)netid1.data, "node2");
  strcpy((char *)netid2->data, "node3");
  fprintf(stdout, "Inserting edge %s to %s\n", (char *)netid1.data, (char *)netid2->data);

  if (graph_ins_edge(&network, &netid1, netid2) != 0) return 1;

  print_graph(&network);

  if ((netid2 = (BfsVertex *)malloc(sizeof(BfsVertex))) == NULL) return 1;

  if ((netid2->data = malloc(STRSIZ)) == NULL) return 1;

  strcpy((char *)netid1.data, "node3");
  strcpy((char *)netid2->data, "node2");
  fprintf(stdout, "Inserting edge %s to %s\n", (char *)netid1.data, (char *)netid2->data);

  if (graph_ins_edge(&network, &netid1, netid2) != 0) return 1;

  print_graph(&network);

  if ((netid2 = (BfsVertex *)malloc(sizeof(BfsVertex))) == NULL) return 1;

  if ((netid2->data = malloc(STRSIZ)) == NULL) return 1;

  strcpy((char *)netid1.data, "node2");
  strcpy((char *)netid2->data, "node4");
  fprintf(stdout, "Inserting edge %s to %s\n", (char *)netid1.data, (char *)netid2->data);

  if (graph_ins_edge(&network, &netid1, netid2) != 0) return 1;

  print_graph(&network);

  if ((netid2 = (BfsVertex *)malloc(sizeof(BfsVertex))) == NULL) return 1;

  if ((netid2->data = malloc(STRSIZ)) == NULL) return 1;

  strcpy((char *)netid1.data, "node4");
  strcpy((char *)netid2->data, "node2");
  fprintf(stdout, "Inserting edge %s to %s\n", (char *)netid1.data, (char *)netid2->data);

  if (graph_ins_edge(&network, &netid1, netid2) != 0) return 1;

  print_graph(&network);

  if ((netid2 = (BfsVertex *)malloc(sizeof(BfsVertex))) == NULL) return 1;

  if ((netid2->data = malloc(STRSIZ)) == NULL) return 1;

  strcpy((char *)netid1.data, "node3");
  strcpy((char *)netid2->data, "node5");
  fprintf(stdout, "Inserting edge %s to %s\n", (char *)netid1.data, (char *)netid2->data);

  if (graph_ins_edge(&network, &netid1, netid2) != 0) return 1;

  print_graph(&network);

  if ((netid2 = (BfsVertex *)malloc(sizeof(BfsVertex))) == NULL) return 1;

  if ((netid2->data = malloc(STRSIZ)) == NULL) return 1;

  strcpy((char *)netid1.data, "node5");
  strcpy((char *)netid2->data, "node3");
  fprintf(stdout, "Inserting edge %s to %s\n", (char *)netid1.data, (char *)netid2->data);

  if (graph_ins_edge(&network, &netid1, netid2) != 0) return 1;

  print_graph(&network);

  if ((netid2 = (BfsVertex *)malloc(sizeof(BfsVertex))) == NULL) return 1;

  if ((netid2->data = malloc(STRSIZ)) == NULL) return 1;

  strcpy((char *)netid1.data, "node4");
  strcpy((char *)netid2->data, "node5");
  fprintf(stdout, "Inserting edge %s to %s\n", (char *)netid1.data, (char *)netid2->data);

  if (graph_ins_edge(&network, &netid1, netid2) != 0) return 1;

  print_graph(&network);

  if ((netid2 = (BfsVertex *)malloc(sizeof(BfsVertex))) == NULL) return 1;

  if ((netid2->data = malloc(STRSIZ)) == NULL) return 1;

  strcpy((char *)netid1.data, "node5");
  strcpy((char *)netid2->data, "node4");
  fprintf(stdout, "Inserting edge %s to %s\n", (char *)netid1.data, (char *)netid2->data);

  if (graph_ins_edge(&network, &netid1, netid2) != 0) return 1;

  print_graph(&network);

  if ((netid2 = (BfsVertex *)malloc(sizeof(BfsVertex))) == NULL) return 1;

  if ((netid2->data = malloc(STRSIZ)) == NULL) return 1;

  strcpy((char *)netid1.data, "node5");
  strcpy((char *)netid2->data, "node6");
  fprintf(stdout, "Inserting edge %s to %s\n", (char *)netid1.data, (char *)netid2->data);

  if (graph_ins_edge(&network, &netid1, netid2) != 0) return 1;

  print_graph(&network);

  if ((netid2 = (BfsVertex *)malloc(sizeof(BfsVertex))) == NULL) return 1;

  if ((netid2->data = malloc(STRSIZ)) == NULL) return 1;

  strcpy((char *)netid1.data, "node6");
  strcpy((char *)netid2->data, "node5");
  fprintf(stdout, "Inserting edge %s to %s\n", (char *)netid1.data, (char *)netid2->data);

  if (graph_ins_edge(&network, &netid1, netid2) != 0)return 1;

  print_graph(&network);

  /// 执行广度优先搜索

  fprintf(stdout, "Generating the breadth-first search listing\n");

  strcpy((char *)netid1.data, "node1");

  if (bfs(&network, &netid1, &list) != 0) return 1;

  i = 0;

  for (element = list_head(&list); element != NULL; element = list_next(element)) {

    netid = list_data(element);
    fprintf(stdout, "-> list[%03d]=%s (color=%d, hops=%d)\n", i,
            (char *)netid->data, netid->color, netid->hops);
    i++;
  }

  /// 销毁列表
  fprintf(stdout, "Destroying the list\n");
  list_destroy(&list);

  /// 销毁图
  fprintf(stdout, "Destroying the graph\n");
  graph_destroy(&network);
  
  return 0;
}
