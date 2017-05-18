//
//  huffman.c
//  Algorithms - Huffman compress
//
//  Created by YourtionGuo on 18/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//


#include <limits.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>

#include "bit.h"
#include "bitree.h"
#include "compress.h"
#include "pqueue.h"

#pragma mark - Private

/**
 比较两棵霍夫曼树的根节点频率

 @param tree1 霍夫曼树1
 @param tree2 霍夫曼树2
 @return tree1 小于 tree1 返回1, tree1 大于 tree1 返回 -1, 相等返回0
 */
static int compare_freq(const void *tree1, const void *tree2)
{
  HuffNode    *root1, *root2;

  /// 比较两棵已经排序的二叉树树根节点

  root1 = (HuffNode *)bitree_data(bitree_root((const BiTree *)tree1));
  root2 = (HuffNode *)bitree_data(bitree_root((const BiTree *)tree2));

  if (root1->freq < root2->freq) return 1;
  if (root1->freq > root2->freq) return -1;
  return 0;
}


/**
 销毁霍夫曼树

 @param tree 霍夫曼树
 */
static void destroy_tree(void *tree)
{
  /// 销毁并回收一棵二叉树空间
  bitree_destroy(tree);
  free(tree);

  return;
}


/**
 通过字节频率建立霍夫曼树

 @param freqs 符号频率数组
 @param tree 构建后的霍夫曼树
 @return 成功返回 0, 否则返回 -1
 */
static int build_tree(int *freqs, BiTree **tree) {

  BiTree      *init, *merge, *left, *right;
  PQueue      pqueue;
  HuffNode    *data;
  int         size, c;

  /// 初始化二叉树优先队列

  *tree = NULL;

  pqueue_init(&pqueue, compare_freq, destroy_tree);

  for (c = 0; c <= UCHAR_MAX; c++) {

    if (freqs[c] != 0) {

      /// 创建二叉树并设置当前符号和频率

      if ((init = (BiTree *)malloc(sizeof(BiTree))) == NULL) {

        pqueue_destroy(&pqueue);
        return -1;
      }

      bitree_init(init, free);

      if ((data = (HuffNode *)malloc(sizeof(HuffNode))) == NULL) {

        pqueue_destroy(&pqueue);
        return -1;
      }

      data->symbol = c;
      data->freq = freqs[c];

      if (bitree_ins_left(init, NULL, data) != 0) {

        free(data);
        bitree_destroy(init);
        free(init);
        pqueue_destroy(&pqueue);
        return -1;
      }

      /// 插入二叉树到优先队列

      if (pqueue_insert(&pqueue, init) != 0) {

        bitree_destroy(init);
        free(init);
        pqueue_destroy(&pqueue);
        return -1;
      }
    }
  }

  /// 通过合并优先队列中的二叉树构建霍夫曼树

  size = pqueue_size(&pqueue);

  for (c = 1; c <= size - 1; c++) {

    /// 创建合并后树的空间

    if ((merge = (BiTree *)malloc(sizeof(BiTree))) == NULL) {

      pqueue_destroy(&pqueue);
      return -1;

    }

    /// 提取出两个根节点最小的两棵二叉树

    if (pqueue_extract(&pqueue, (void **)&left) != 0) {

      pqueue_destroy(&pqueue);
      free(merge);
      return -1;
    }

    if (pqueue_extract(&pqueue, (void **)&right) != 0) {

      pqueue_destroy(&pqueue);
      free(merge);
      return -1;
    }

    /// 创建合并后根节点的数据空间

    if ((data = (HuffNode *)malloc(sizeof(HuffNode))) == NULL) {

      pqueue_destroy(&pqueue);
      free(merge);
      return -1;
    }

    memset(data, 0, sizeof(HuffNode));

    /// 计算已经合并二叉树根节点的频率值（求和子节点）

    data->freq = ((HuffNode *)bitree_data(bitree_root(left)))->freq +
                 ((HuffNode *)bitree_data(bitree_root(right)))->freq;

    /// 合并两棵树

    if (bitree_merge(merge, left, right, data) != 0) {

      pqueue_destroy(&pqueue);
      free(merge);
      return -1;
    }

    /// 将合并的二叉树插入回优先队列并释放相关的空间

    if (pqueue_insert(&pqueue, merge) != 0) {

      pqueue_destroy(&pqueue);
      bitree_destroy(merge);
      free(merge);
      return -1;
    }

    free(left);
    free(right);
  }

  /// 优先队列中剩余的最后一棵二叉树就是霍夫曼树

  if (pqueue_extract(&pqueue, (void **)tree) != 0) {

    pqueue_destroy(&pqueue);
    return -1;

  } else {

    pqueue_destroy(&pqueue);
  }

  return 0;
}


/**
 建立霍夫曼编码表

 @param node 霍夫曼树结点
 @param code 当前生成的霍夫曼编码
 @param size 编码的位数
 @param table 霍夫曼编码结果
 */
static void build_table(BiTreeNode *node, unsigned short code, unsigned char size, HuffCode *table) {

  if (!bitree_is_eob(node)) {

    if (!bitree_is_eob(bitree_left(node))) {

      /// 向左移动并在编码末尾追加 0
      build_table(bitree_left(node), code << 1, size + 1, table);
    }

    if (!bitree_is_eob(bitree_right(node))) {

      /// 向右移动并在编码末尾追加 1
      build_table(bitree_right(node), (code << 1) | 0x0001, size + 1, table);
    }

    if (bitree_is_eob(bitree_left(node))&&bitree_is_eob(bitree_right(node))) {

      /// 确保当前编码是以大端字节格式存放
      code = htons(code);

      /// 将当前符号编码插入叶子节点

      table[((HuffNode *)bitree_data(node))->symbol].used = 1;
      table[((HuffNode *)bitree_data(node))->symbol].code = code;
      table[((HuffNode *)bitree_data(node))->symbol].size = size;
    }
  }

  return;
}


#pragma mark - Public


int huffman_compress(const unsigned char *original, unsigned char **compressed, int size)
{
  BiTree          *tree;
  HuffCode        table[UCHAR_MAX + 1];
  int             freqs[UCHAR_MAX + 1], max, scale, hsize, ipos, opos, cpos, c, i;
  unsigned char   *comp, *temp;

  /// 初始化最初的压缩结果为空
  *compressed = NULL;

  /// 获取原始数据中每个符号的频率

  for (c = 0; c <= UCHAR_MAX; c++) {
    freqs[c] = 0;
  }

  ipos = 0;

  if (size > 0) {

    while (ipos < size) {

      freqs[original[ipos]]++;
      ipos++;
    }
  }

  /// 缩放频率以适应一个 byte 大小（可以只用一个字节来表示）

  max = UCHAR_MAX;

  for (c = 0; c <= UCHAR_MAX; c++) {

    if (freqs[c] > max) {
      max = freqs[c];
    }
  }

  for (c = 0; c <= UCHAR_MAX; c++) {

    scale = (int)(freqs[c] / ((double)max / (double)UCHAR_MAX));

    if (scale == 0 && freqs[c] != 0) {
      /// 确保当任何非 0 频率值其缩减为小于 1 时，最终应该将其设为 1 而不是 0
      freqs[c] = 1;
    } else {
      freqs[c] = scale;
    }
  }

  /// 构建霍夫曼树和霍夫曼编码表

  if (build_tree(freqs, &tree) != 0) return -1;

  for (c = 0; c <= UCHAR_MAX; c++) {
    memset(&table[c], 0, sizeof(HuffCode));
  }

  build_table(bitree_root(tree), 0x0000, 0, table);

  bitree_destroy(tree);
  free(tree);

  /// 写入头部信息

  hsize = sizeof(int) + (UCHAR_MAX + 1);

  if ((comp = (unsigned char *)malloc(hsize)) == NULL) return -1;

  memcpy(comp, &size, sizeof(int));

  for (c = 0; c <= UCHAR_MAX; c++) {
    comp[sizeof(int) + c] = (unsigned char)freqs[c];
  }

  /// 压缩数据

  ipos = 0;
  opos = hsize * 8;

  while (ipos < size) {

    /// 获取原始数据中的下一个符号
    c = original[ipos];

    /// 将当前符号的 code 写入压缩后数据

    for (i = 0; i < table[c].size; i++) {

      if (opos % 8 == 0) {

        /// 创建另外一个 byte 用于存放压缩数据
        if ((temp = (unsigned char *)realloc(comp,(opos / 8) + 1)) == NULL) {

          free(comp);
          return -1;
        }

        comp = temp;

      }

      cpos = (sizeof(short) * 8) - table[c].size + i;
      bit_set(comp, opos, bit_get((unsigned char *)&table[c].code, cpos));
      opos++;

    }

    ipos++;
  }

  /// 将缓冲区指向已压缩数据
  *compressed = comp;

  /// 返回压缩后数据的长度
  return ((opos - 1) / 8) + 1;
}


int huffman_uncompress(const unsigned char *compressed, unsigned char **original)
{
  BiTree          *tree;
  BiTreeNode      *node;
  int             freqs[UCHAR_MAX + 1], hsize, size, ipos, opos, state, c;
  unsigned char   *orig, *temp;

  /// 初始化最初的解压结果为空
  *original = orig = NULL;

  /// 获取压缩数据中的头部信息

  hsize = sizeof(int) + (UCHAR_MAX + 1);
  memcpy(&size, compressed, sizeof(int));

  for (c = 0; c <= UCHAR_MAX; c++) {
    freqs[c] = compressed[sizeof(int) + c];
  }

  /// 通过获取的头部信息构建压缩数据时用的霍夫曼树
  if (build_tree(freqs, &tree) != 0) return -1;

  /// 解压数据

  ipos = hsize * 8;
  opos = 0;
  node = bitree_root(tree);

  while (opos < size) {

    /// 获取压缩数据中的下一位
    state = bit_get(compressed, ipos);
    ipos++;

    if (state == 0) {

      /// 向左移动

      if (bitree_is_eob(node) || bitree_is_eob(bitree_left(node))) {

        bitree_destroy(tree);
        free(tree);
        return -1;

      } else {
        node = bitree_left(node);
      }
    } else {

      /// 向右移动

      if (bitree_is_eob(node) || bitree_is_eob(bitree_right(node))) {

        bitree_destroy(tree);
        free(tree);
        return -1;
      } else {
        node = bitree_right(node);
      }
    }

    if (bitree_is_eob(bitree_left(node))&&bitree_is_eob(bitree_right(node))) {

      /// 将叶子节点中的符号写回解压数据

      if (opos > 0) {

        if ((temp = (unsigned char *)realloc(orig, opos + 1)) == NULL) {

          bitree_destroy(tree);
          free(tree);
          free(orig);
          return -1;
        }

        orig = temp;

      } else {

        if ((orig = (unsigned char *)malloc(1)) == NULL) {

          bitree_destroy(tree);
          free(tree);
          return -1;
        }
      }

      orig[opos] = ((HuffNode *)bitree_data(node))->symbol;
      opos++;

      /// 移回树的根节点
      node = bitree_root(tree);
    }
  }
  
  bitree_destroy(tree);
  free(tree);
  
  /// 将缓冲区指向已解压数据
  *original = orig;
  
  /// 返回解压后数据大小
  return opos;
}
