//
//  geodist.h
//  Algorithms - Geo dist
//
//  Created by YourtionGuo on 25/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#ifndef GEODIST_H
#define GEODIST_H

/// 地球半径
#define     EARTH_RADIUS      3440.065

/**
 计算地球上两点间近似距离 - O(1)

 @param lat1 地点 1 经度
 @param lon1 地点 1 纬度
 @param lat2 地点 2 经度
 @param lon2 地点 2 纬度
 @param d 近似距离结果
 @return 计算成功返回0；否则，返回-1
 */
int geodist(double lat1, double lon1, double lat2, double lon2, double *d);

#endif /* GEODIST_H */
