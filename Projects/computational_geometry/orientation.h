#ifndef ORIENTATIONDEF
#define ORIENTATIONDEF
#include "point.h"

#include<iostream>
#include <algorithm> 
class orientation
{
 protected:
  int direct;
  

 public:
  // Constructor

 int get_orientation(point p, point q , point r){
	
	direct = (q.y-p.y)*(r.x-q.x) - (r.y-q.y)*(q.x-p.x);
	
	if(direct == 0)  //colinear
	return 0;


	return (direct > 0) ? 1:2; // clockwise or anti clockwise

}
	bool colinearpoints(point p, point q, point r)
{
    if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
        q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
       return true;
 
    return false;
}

bool doIntersect(point p1, point q1, point p2, point q2)
{
    // Find the four orientations needed for general and
    // special cases
    int o1 = get_orientation(p1, q1, p2);
    int o2 = get_orientation(p1, q1, q2);
    int o3 = get_orientation(p2, q2, p1);
    int o4 = get_orientation(p2, q2, q1);
 
    // General case
    if (o1 != o2 && o3 != o4)
        return true;
 
    // Special Cases
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    if (o1 == 0 && colinearpoints(p1, p2, q1)) return true;
 
    // p1, q1 and p2 are colinear and q2 lies on segment p1q1
    if (o2 == 0 && colinearpoints(p1, q2, q1)) return true;
 
    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if (o3 == 0 && colinearpoints(p2, p1, q2)) return true;
 
     // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    if (o4 == 0 && colinearpoints(p2, q1, q2)) return true;
 
    return false; // Doesn't fall in any of the above cases
}


};
#endif
