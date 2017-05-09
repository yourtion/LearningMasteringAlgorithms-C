//
//  bfs.h
//  Algorithms - Graph breadth-first search
//
//  Created by YourtionGuo on 08/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#ifndef BFS_H
#define BFS_H

#include "graph.h"
#include "list.h"


/**
 广度优先搜索
 */
typedef struct BfsVertex_
{
  void          *data;

  VertexColor   color;
  int                hops;

} BfsVertex;


/**
 在 graph 指定的图执行广度优先搜索 - O(V+E) V是图中顶点的个数，E是边的个数

 @param graph 图
 @param start 起始的顶点
 @param hops 跳数链表
 @return 成功返回0；否则返回-1
 */
int bfs(Graph *graph, BfsVertex *start, List *hops);

#endif /* BFS_H */
