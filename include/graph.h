//
//  graph.h
//  Algorithms - Graph
//
//  Created by YourtionGuo on 08/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>

#include "list.h"
#include "set.h"


/**
 邻接表
 */
typedef struct AdjList_
{
  void      *vertex;
  Set       adjacent;

} AdjList;


/**
 图
 */
typedef struct Graph_
{
  int       vcount;
  int       ecount;

  int       (*match)(const void *key1, const void *key2);
  void      (*destroy)(void *data);

  List      adjlists;

} Graph;

/**
 结点颜色
 */
typedef enum VertexColor_ {white, gray, black} VertexColor;


/**
 初始化由参数 graph 所指定的图 - O(1)

 @param graph 图
 @param match 函数指针，用于判断两个成员是否相匹配（等于返回 1，否则返回 0）
 @param destroy 成员析构函数（free...）
 */
void graph_init(Graph *graph,
                int (*match)(const void *key1, const void *key2),
                void (*destroy)(void *data));


/**
 销毁由参数 graph 所指定的图 - O(V+E) V是图中顶点的个数，E是边的个数

 @param graph 图
 */
void graph_destroy(Graph *graph);


/**
 将顶点插入由参数 graph 所指定的图中 - O(V)

 @param graph 图
 @param data 顶点数据
 @return 插入成功返回0；顶点已经存在返回1；否则返回-1
 */
int graph_ins_vertex(Graph *graph, const void *data);


/**
 将由 data1 以及 data2 所指定的顶点构成的边插入图 graph 中 - O(V)

 @param graph 图
 @param data1 顶点1数据
 @param data2 顶点2数据
 @return 插入成功返回0；边已存在返回1；否则返回-1
 */
int graph_ins_edge(Graph *graph, const void *data1, const void *data2);


/**
 从 graph 指定的图中移除与 data 相匹配的顶点 - O(V+E)

 @param graph 图
 @param data 顶点
 @return 移除成功返回0；否则返回-1
 */
int graph_rem_vertex(Graph *graph, void **data);


/**
 从 graph 指定的图中移除从 data1 到 data2 的边 - O(V)

 @param graph 图
 @param data1 顶点1数据
 @param data2 顶点2数据
 @return 移除成功，返回0；否则返回-1
 */
int graph_rem_edge(Graph *graph, void *data1, void **data2);


/**
 取出 graph 中由 data 所指定的顶点的邻接表 - O(V)

 @param graph 图
 @param data 顶点
 @param adjlist 顶点的邻接表
 @return 取得邻接表成功返回0；否则返回-1
 */
int graph_adjlist(const Graph *graph, const void *data, AdjList **adjlist);


/**
 判断由 data2 所指定的顶点是否与 graph 中由 data1 所指定的顶点邻接 - O(V)

 @param graph 图
 @param data1 顶点1数据
 @param data2 顶点2数据
 @return 如果顶点2与顶点1邻接返回1；否则返回0
 */
int graph_is_adjacent(const Graph *graph, const void *data1, const void *data2);


/**
 返回由参数 graph 所指定的图中的邻接表结构链表 - O(1)

 @param graph 图
 @return 由邻接表结构所组成的链表
 */
#define graph_adjlists(graph) ((graph)->adjlists)


/**
 计算 graph 指定的图中顶点的个数 - O(1)

 @param graph 图
 @return 顶点个数
 */
#define graph_vcount(graph) ((graph)->vcount)


/**
 计算 graph 指定的图中边的个数 - O(1)

 @param graph 图
 @return 边的个数
 */
#define graph_ecount(graph) ((graph)->ecount)

#endif /* GRAPH_H */
