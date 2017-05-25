//
//  cvxhull.c
//  Algorithms - Convex hull (Jarvis's march)
//
//  Created by YourtionGuo on 25/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <math.h>
#include <stdlib.h>

#include "geometry.h"
#include "list.h"

#pragma mark - Public


int cvxhull(const List *P, List *polygon)
{
  ListElmt    *element;
  Point       *min, *low = NULL, *p0, *pi, *pc = NULL;
  double      z, length1, length2;
  int         count;
  
  /// 确定点集P中的最低点

  min = list_data(list_head(P));

  for (element = list_head(P); element != NULL; element = list_next(element)) {

    p0 = list_data(element);

    /// 继续跟踪最低点

    if (p0->y < min->y) {

      min = p0;
      low = list_data(element);

    } else {

      /// 如果发生冲突，使用最左点

      if (p0->y == min->y && p0->x < min->x) {

        min = p0;
        low = list_data(element);

      }
    }
  }

  /// 初始化凸包结果链表
  list_init(polygon, NULL);

  /// 使用 Jarvis's march 进行凸包检测

  p0 = low;

  do {

    /// 插入新的 p0 到凸包
    if (list_ins_next(polygon, list_tail(polygon), p0) != 0) {

      list_destroy(polygon);
      return -1;

    }

    /// 找到顺时针方向的其他点
    count = 0;

    for (element = list_head(P); element != NULL; element = list_next(element)) {

      /// 跳过列表中的 p0
      if ((pi = list_data(element)) == p0) continue;

      /// 统计已经发现点的个数
      count++;

      /// 假设第一个点就是其他点的顺时针点，除非找到多个
      if (count == 1) {

        pc = list_data(element);
        continue;

      }

      /// 判断 pi 是不是在 pc 的顺时针方法
      if ((z = ((pi->x - p0->x) * (pc->y - p0->y)) - ((pi->y - p0->y) * (pc->x - p0->x))) > 0) {

        /// pi 在 pc 的顺时针方法
        pc = pi;

      } else if (z == 0) {

        /// 如果 pi 和 pc 共线，选择距离 p0 远的点
        length1 = sqrt(pow(pi->x - p0->x, 2.0) + pow(pi->y - p0->y, 2.0));
        length2 = sqrt(pow(pc->x - p0->x, 2.0) + pow(pc->y - p0->y, 2.0));

        if (length1 > length2) {
          /// pi 比 pc 距离 p0 更远
          pc = pi;
        }
      }
    }

    /// 准备查找下一个点
    p0 = pc;

    /// 执行直到回到最低点
  } while (p0 != low);
  
  return 0;
}
