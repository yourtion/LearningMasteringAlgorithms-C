//
//  symbol.h
//  Algorithms - lex Symbol
//
//  Created by YourtionGuo on 28/04/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#ifndef SYMBOL_H
#define SYMBOL_H


/**
 模拟输入流拆分函数

 @param istream 输入流
 @return 标记（ NULL 表示结束）
 */
static char *next_token(const char *istream)
{
  return NULL;
}


/**
 符号标记
 */
typedef struct
{
  char               *lexeme;
  Token              token;
  
} Symbol;

#endif /* SYMBOL_H */
