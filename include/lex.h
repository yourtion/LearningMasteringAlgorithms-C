//
//  lex.h
//  Algorithms - lex
//
//  Created by YourtionGuo on 28/04/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#ifndef LEX_H
#define LEX_H

#include "chtbl.h"

typedef enum Token_ {lexit, error, digit, other} Token;


/**
 根据输入流生成符号表

 @param istream 输入流
 @param symtbl 符号表
 @return 类型
 */
Token lex(const char *istream, CHTbl *symtbl);

#endif /* LEX_H */
