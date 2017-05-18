//
//  transfer.h
//  Algorithms - Network transfer
//
//  Created by YourtionGuo on 18/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#ifndef TRANSFER_H
#define TRANSFER_H


/**
 首先压缩数据，然后调用标准套接字函数 send

 @param s 已经建立连接的套接字描述符
 @param data 要发送数据的缓冲区
 @param size 缓冲区大小
 @param flags 传入 send 的正常 flags 参数
 @return 成功返回0；否则返回-1
 */
int send_comp(int s, const unsigned char *data, int size, int flags);


/**
 使用标准套接字函数 recv 接收从 send_comp 发送过来的数据

 @param s 已经建立连接的套接字描述符
 @param data 指向解压缩数据的指针
 @param size data 的大小（由recv_comp的返回值决定）
 @param flags 传入 recv 的正常 flags 参数
 @return 成功返回0；否则返回-1
 */
int recv_comp(int s, unsigned char **data, int *size, int flags);

#endif /* TRANSFER_H */
