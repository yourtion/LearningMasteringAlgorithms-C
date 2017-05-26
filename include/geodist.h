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
 <#Description#>

 @param lat1 <#lat1 description#>
 @param lon1 <#lon1 description#>
 @param lat2 <#lat2 description#>
 @param lon2 <#lon2 description#>
 @param d <#d description#>
 @return <#return value description#>
 */
int geodist(double lat1, double lon1, double lat2, double lon2, double *d);

#endif /* GEODIST_H */
