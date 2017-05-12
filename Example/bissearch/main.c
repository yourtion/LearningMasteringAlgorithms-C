//
//  main.c
//  MasteringAlgorithms
//  Description: Illustrates searching algorithms (see Chapter 12).
//
//  Created by YourtionGuo on 11/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <stdio.h>
#include <string.h>

#include "search.h"
#include "sort.h"

/// 定义字符串长度
#define     STRSIZ      6

static int compare_str(const void *key1, const void *key2)
{
  int       retval;

  /// 比较两个字符
  if ((retval = strcmp((const char *)key1, (const char *)key2)) > 0) return 1;
  if (retval < 0) return -1;
  return 0;
}

/// 搜索词定义
typedef enum Words_ {hop, hat, tap, bat, tip, mop, mom, cat, zoo, wax, top, dip} Words;


int main(int argc, char **argv)
{
  char      *target;
  char      sarray[12][STRSIZ], tarray[12][STRSIZ];
  Words     word;
  int       retval;

  /// 初始化搜索词
  strcpy(sarray[hop], "hop");
  strcpy(sarray[hat], "hat");
  strcpy(sarray[tap], "tap");
  strcpy(sarray[bat], "bat");
  strcpy(sarray[tip], "tip");
  strcpy(sarray[mop], "mop");
  strcpy(sarray[mom], "mom");
  strcpy(sarray[cat], "cat");
  strcpy(sarray[zoo], "zoo");
  strcpy(sarray[wax], "wax");
  strcpy(sarray[top], "top");
  strcpy(sarray[dip], "dip");

  /// 执行二分搜索

  fprintf(stdout, "Performing binary search\n");

  strcpy(tarray[0], "bat");
  strcpy(tarray[1], "top");
  strcpy(tarray[2], "xxx");

  issort(sarray, 12, STRSIZ, compare_str);

  for (word = hop; word <= dip; word++) {
    fprintf(stdout, "-> sorted[%02d]=%s\n", word, (char *)sarray[word]);
  }

  target = tarray[0];
  retval = bisearch(sarray, target, 12, STRSIZ, compare_str);

  if (retval < 0) {
    fprintf(stdout, "Could not find %s\n", target);
  } else {
    fprintf(stdout, "Found %s at position %d\n", target, retval);
  }

  target = tarray[1];
  retval = bisearch(sarray, target, 12, STRSIZ, compare_str);

  if (retval < 0) {
    fprintf(stdout, "Could not find %s\n", target);
  } else {
    fprintf(stdout, "Found %s at position %d\n", target, retval);
  }

  target = tarray[2];
  retval = bisearch(sarray, target, 12, STRSIZ, compare_str);
  
  if (retval < 0) {
    fprintf(stdout, "Could not find %s\n", target);
  } else {
    fprintf(stdout, "Found %s at position %d\n", target, retval);
  }

  return 0;
}
