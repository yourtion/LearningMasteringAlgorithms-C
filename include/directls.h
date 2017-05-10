//
//  directls.h
//  Algorithms - Sorting a directory listing
//
//  Created by YourtionGuo on 10/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#ifndef DIRECTLS_H
#define DIRECTLS_H

#include <dirent.h>


/**
 目录结构
 */
typedef struct Directory_
{
  char      name[MAXNAMLEN + 1];

} Directory;


/**
 列出 path 路径中指定的目录列表

 @param path 路径
 @param dir 目录列表
 @return 成功返回 0；否则返回 -1
 */
int directls(const char *path, Directory **dir);

#endif /* DIRECTLS_H */
