//
//  spell.c
//  Algorithms - Spell checking
//
//  Created by YourtionGuo on 11/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <string.h>

#include "search.h"
#include "spell.h"

#pragma mark - Private

static int compare_str(const void *str1, const void *str2)
{
  int       retval;

  /// 比较两个字符
  if ((retval = strcmp((const char *)str1, (const char *)str2)) > 0) return 1;
  if (retval < 0) return -1;
  return 0;
}

#pragma mark - Public

int spell(char (*dictionary)[SPELL_SIZE], int size, const char *word)
{
  /// 查找单词
  if (bisearch(dictionary, word, size, SPELL_SIZE, compare_str) >= 0) return 1;
  return 0;
}
