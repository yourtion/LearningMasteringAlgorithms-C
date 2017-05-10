//
//  directls.c
//  Algorithms - Sorting a directory listing
//
//  Created by YourtionGuo on 10/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "directls.h"
#include "sort.h"

#pragma mark - Private


/**
 比较两个目录

 @param key1 目录1
 @param key2 目录2
 @return 大于返回 1，小于返回 -1，等于返回 0
 */
static int compare_dir(const void *key1, const void *key2)
{
  int retval = strcmp(((const Directory *)key1)->name, ((const Directory *)key2)->name);

  if (retval > 0) return 1;
  if (retval < 0) return -1;
  return 0;
}


#pragma mark - Public

int directls(const char *path, Directory **dir)
{
  DIR             *dirptr;
  Directory       *temp;
  struct dirent   *curdir;
  int             count;

  /// 打开目录
  if ((dirptr = opendir(path)) == NULL) return -1;

  /// 获得目录内容

  *dir = NULL;
  count = 0;

  while ((curdir = readdir(dirptr)) != NULL) {

    count++;

    if ((temp = (Directory *)realloc(*dir, count * sizeof(Directory))) == NULL) {

      free(*dir);
      return -1;

    } else {

      *dir = temp;
    }

    strcpy(((*dir)[count - 1]).name, curdir->d_name);
  }

  closedir(dirptr);

  /// 对目录中条目按照名字进行排序
  if (qksort(*dir, count, sizeof(Directory), 0, count - 1, compare_dir) != 0) return -1;

  /// 返回目录条目数量
  return count;
}
