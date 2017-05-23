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

/*****************************************************************************
 *                                                                            *
 *  Define a structure for vertices in minimum spanning trees.                *
 *                                                                            *
 *****************************************************************************/

typedef struct MstVertex_
{
  void               *data;
  double             weight;

  VertexColor        color;
  double             key;

  struct MstVertex_  *parent;

} MstVertex;

/*****************************************************************************
 *                                                                            *
 *  Define a structure for vertices in shortest-path problems.                *
 *                                                                            *
 *****************************************************************************/

typedef struct PathVertex_
{
  void               *data;
  double             weight;

  VertexColor        color;
  double             d;

  struct PathVertex_ *parent;

} PathVertex;

/*****************************************************************************
 *                                                                            *
 *  Define a structure for vertices in traveling-salesman problems.           *
 *                                                                            *
 *****************************************************************************/

typedef struct TspVertex_
{
  void               *data;

  double             x,
  y;

  VertexColor        color;

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
 <#Description#>

 @param graph <#graph description#>
 @param start <#start description#>
 @param paths <#paths description#>
 @param match <#match description#>
 @return <#return value description#>
 */
int shortest(Graph *graph, const PathVertex *start, List *paths,
             int (*match)(const void *key1, const void *key2));


/**
 <#Description#>

 @param vertices <#vertices description#>
 @param start <#start description#>
 @param tour <#tour description#>
 @param match <#match description#>
 @return <#return value description#>
 */
int tsp(List *vertices, const TspVertex *start, List *tour,
        int (*match)(const void *key1, const void *key2));

#endif /* GRAPHALG_H */
