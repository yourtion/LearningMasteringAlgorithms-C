//
//  dfs.h
//  Algorithms - Graph depth-first search
//
//  Created by YourtionGuo on 08/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#ifndef DFS_H
#define DFS_H

#include "graph.h"
#include "list.h"


/**
 深度优先搜索
 */
typedef struct DfsVertex_ {

  void               *data;

  VertexColor        color;

} DfsVertex;


/**
 在 graph 指定的图执行深度优先搜索 - O(V+E) V是图中顶点的个数，E是边的个数

 @param graph 图
 @param ordered 顶点链表
 @return 成功返回0；否则返回-1
 */
int dfs(Graph *graph, List *ordered);

#endif /* DFS_H */
