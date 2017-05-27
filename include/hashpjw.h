//
//  hashpjw.h
//  Algorithms - hash function
//
//  Created by YourtionGuo on 28/04/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#ifndef HASHPJW_H
#define HASHPJW_H

/// 定义桶数量（表大小）
#define     PRIME_TBLSIZ       1699


/**
 处理字符串的哈希函数

 @param key 待处理键
 @return 哈希
 */
int hashpjw(const void *key);

#endif /* HASHPJW_H */
