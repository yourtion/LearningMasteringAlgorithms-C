//
//  spell.h
//  Algorithms - Spell checking
//
//  Created by YourtionGuo on 11/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#ifndef SPELL_H
#define SPELL_H

/// 设置单词最大长度
#define     SPELL_SIZE      31


/**
 单词拼写检查 - O(lgn)

 @param dictionary 有序字符串数组
 @param size 字典中字符串的个数
 @param word 被检查的单词
 @return 找到返回 1；否则返回 0
 */
int spell(char (*dictionary)[SPELL_SIZE], int size, const char *word);

#endif /* SPELL_H */
