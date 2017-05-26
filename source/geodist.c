//
//  geodist.c
//  Algorithms - Geo dist
//
//  Created by YourtionGuo on 25/05/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include "geodist.h"
#include "geometry.h"

int geodist(double lat1, double lon1, double lat2, double lon2, double *d)
{

  SPoint      p1, p2;

  /*****************************************************************************
   *                                                                            *
   *  Validate the coordinates.                                                 *
   *                                                                            *
   *****************************************************************************/

  if (lat1 <  -90.0 || lat1 >  90.0 || lat2 <  -90.0 || lat2 >  90.0)
    return -1;

  if (lon1 < -180.0 || lon1 > 180.0 || lon2 < -180.0 || lon2 > 180.0)
    return -1;

  /*****************************************************************************
   *                                                                            *
   *  Convert each latitude and longitude to spherical coordinates in radians   *
   *  using the earth's radius for rho.                                         *
   *                                                                            *
   *****************************************************************************/

  p1.rho = EARTH_RADIUS;
  p1.theta = -1.0 * DEGTORAD(lon1);
  p1.phi = (DEGTORAD(-1.0 * lat1)) + DEGTORAD(90.0);

  p2.rho = EARTH_RADIUS;
  p2.theta = -1.0 * DEGTORAD(lon2);
  p2.phi = (DEGTORAD(-1.0 * lat2)) + DEGTORAD(90.0);

  /*****************************************************************************
   *                                                                            *
   *  Compute the distance between the points.                                  *
   *                                                                            *
   *****************************************************************************/
  
  arclen(p1, p2, d);
  
  return 0;
}

