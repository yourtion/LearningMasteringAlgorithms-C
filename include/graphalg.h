//
//  graphalg.h
//  Algorithms - Graph algorithms
//
//  Created by YourtionGuo on 23/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#ifndef GRAPHALG_H
#define GRAPHALG_H

#include "graph.h"
#include "list.h"


/**
 最小生成树顶点
 */
typedef struct MstVertex_
{
  void               *data;   // 顶点的数据
  double             weight;  // 边的权值

  VertexColor        color;   // 顶点的色值
  double             key;     // 顶点的键值

  struct MstVertex_  *parent; // 顶点的父结点

} MstVertex;


/**
 最短路径顶点
 */
typedef struct PathVertex_
{
  void               *data;   // 顶点的数据
  double             weight;  // 边的权值

  VertexColor        color;   // 顶点的色值
  double             d;       // 顶点的最短路径估计

  struct PathVertex_ *parent; // 顶点的父结点

} PathVertex;

/**
 旅行商问题顶点
 */
typedef struct TspVertex_
{
  void          *data;  // 顶点的数据

  double        x, y;   // 顶点的坐标

  VertexColor   color;  // 顶点的色值

} TspVertex;


/**
 为一个无方向的带权图 graph 计算最小生成树 - O(EV^2) V是图中顶点的个数，E是边的条数

 @param graph 无方向的带权图
 @param start 顶点
 @param span 最小生成树的相关数据
 @param match 函数指针，用于判断两个成员是否相匹配（等于返回 1，否则返回 0）
 @return 计算最小生成树成功返回0；否则，返回-1
 */
int mst(Graph *graph, const MstVertex *start, List *span,
        int (*match)(const void *key1, const void *key2));


/**
 计算顶点 start 与有向带权图 graph 中其他所有顶点之间的最短路径 - O(EV^2) V是图中顶点的个数，E是边的条数

 @param graph 有向带权图
 @param start 顶点
 @param paths 最短路径的相关数据
 @param match 函数指针，用于判断两个成员是否相匹配（等于返回 1，否则返回 0）
 @return 计算最短路径成功返回0；否则，返回-1
 */
int shortest(Graph *graph, const PathVertex *start, List *paths,
             int (*match)(const void *key1, const void *key2));


/**
 为存储在 vertices 中的顶点计算一条近似旅行商的路线 - O(V^2) V是路线中要访问顶点的个数

 @param vertices 顶点列表
 @param start 顶点
 @param tour 计算得到的路线
 @param match 函数指针，用于判断两个成员是否相匹配（等于返回 1，否则返回 0）
 @return 计算近似旅行商路线成功返回0；否则，返回-1
 */
int tsp(List *vertices, const TspVertex *start, List *tour,
        int (*match)(const void *key1, const void *key2));

#endif /* GRAPHALG_H */
