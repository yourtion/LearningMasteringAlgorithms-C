//
//  main.c
//  MasteringAlgorithms
//  Description: Illustrates spell checking (see Chapter 12). 
//
//  Created by YourtionGuo on 11/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "search.h"
#include "sort.h"
#include "spell.h"

static int compare_str(const void *key1, const void *key2)
{
  int       retval;

  /// 比较两个字符
  if ((retval = strcmp((const char *)key1, (const char *)key2)) > 0) return 1;
  if (retval < 0) return -1;
  return 0;
}


int main(int argc, char **argv)
{
  char      dictionary[12][SPELL_SIZE], lookup[SPELL_SIZE], target[SPELL_SIZE];
  int       i;

  /// 创建已排序单词字典

  strcpy(dictionary[ 0], "HOP");
  strcpy(dictionary[ 1], "HAT");
  strcpy(dictionary[ 2], "TAP");
  strcpy(dictionary[ 3], "BAT");
  strcpy(dictionary[ 4], "TIP");
  strcpy(dictionary[ 5], "MOP");
  strcpy(dictionary[ 6], "MOM");
  strcpy(dictionary[ 7], "CAT");
  strcpy(dictionary[ 8], "ZOO");
  strcpy(dictionary[ 9], "WAX");
  strcpy(dictionary[10], "TOP");
  strcpy(dictionary[11], "DIP");

  if (issort(dictionary, 12, SPELL_SIZE, compare_str) != 0) return 1;

  /// 执行单词拼写

  strcpy(lookup, "hat");
  memset(target, 0, SPELL_SIZE);

  for (i = 0; i < strlen(lookup); i++) {
    target[i] = toupper(lookup[i]);
  }

  if (spell(dictionary, 12, target)) {
    fprintf(stdout, "%s is spelled correctly\n", lookup);
  } else {
    fprintf(stdout, "%s is not spelled correctly\n", lookup);
  }

  strcpy(lookup, "dop");
  memset(target, 0, SPELL_SIZE);

  for (i = 0; i < strlen(lookup); i++) {
    target[i] = toupper(lookup[i]);
  }

  if (spell(dictionary, 12, target)) {
    fprintf(stdout, "%s is spelled correctly\n", lookup);
  } else {
    fprintf(stdout, "%s is not spelled correctly\n", lookup);
  }

  strcpy(lookup, "dip");
  memset(target, 0, SPELL_SIZE);

  for (i = 0; i < strlen(lookup); i++) {
    target[i] = toupper(lookup[i]);
  }

  if (spell(dictionary, 12, target)) {
    fprintf(stdout, "%s is spelled correctly\n", lookup);
  } else {
    fprintf(stdout, "%s is not spelled correctly\n", lookup);
  }
  
  return 0;
}
