//
//  main.c
//  MasteringAlgorithms
//  Description: Illustrates sorting a directory listing (see Chapter 12).
//
//  Created by YourtionGuo on 10/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <stdio.h>
#include <sys/param.h>
#include <unistd.h>
#include <stdlib.h>

#include "directls.h"


int main(int argc, char **argv)
{
  Directory   *dir;
  char        buffer[MAXPATHLEN];
  int         count, i;

  /// 获取目录列表

  if (argc > 1) {

    if ((count = directls(argv[1], &dir)) < 0) {

      fprintf(stdout, "Could not read directory\n");
      exit(1);
      
    }

  } else {

    if ((count = directls(getcwd(buffer, MAXPATHLEN), &dir)) < 0) {

      fprintf(stdout, "Could not read directory\n");
      exit(1);

    }
  }

  /// 列出目录

  for (i = 0; i < count; i++) {
    fprintf(stdout, "%s\n", dir[i].name);
  }

  fprintf(stdout, "%d found\n", count);
  free(dir);
  
  return 0;
}

