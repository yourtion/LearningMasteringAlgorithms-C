//
//  lex.c
//  Algorithms - lex
//
//  Created by YourtionGuo on 28/04/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "chtbl.h"
#include "lex.h"
#include "symbol.h"

#pragma mark - Public


Token lex(const char *istream, CHTbl *symtbl)
{
  
  Token     token;
  Symbol    *symbol;
  int       length, retval, i;

  /// 创建符号表的空间
  if ((symbol = (Symbol *)malloc(sizeof(Symbol))) == NULL) return error;
  
  /// 对输入流进行分割
  if ((symbol->lexeme = next_token(istream)) == NULL) {
    
    /// 如果没有更多数据则返回
    free(symbol);
    return lexit;
    
  } else {
    
    /// 判断符号类型
    symbol->token = digit;
    length = (int)strlen(symbol->lexeme);
    
    for (i = 0; i < length; i++) {
      
      if (!isdigit(symbol->lexeme[i])) {
        symbol->token = other;
      }
    }
    
    memcpy(&token, &symbol->token, sizeof(Token));
    
    /// 插入到符号表
    if ((retval = chtbl_insert(symtbl, symbol)) < 0) {
      
      free(symbol);
      return error;
      
    } else if (retval == 1) {
      
      /// 符号已经存在
      free(symbol);
    }
  }
  
  /// 返回结果
  return token;
}
