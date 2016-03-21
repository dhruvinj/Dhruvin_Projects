#include<iostream>

#include "point.h"
#include "orientation.h"


int main(int argc, char* argv[])
{
	
 	point p1(0, 0), p2(4, 4), p3 (1, 2);
	orientation s;
    int o = s.get_orientation(p1, p2, p3);
    if (o==0)         std::cout << "Linear"<< std::endl;
    else if (o == 1)  std::cout << "Clockwise"<< std::endl;
    else              std::cout << "CounterClockwise" << std::endl;
    

	 point p1(1, 1), q1(10, 1), p2(1, 2), q2 (10, 2);
 	
    s.doIntersect(p1, q1, p2, q2)? std::cout << "Yes\n": std::cout << "No\n";
	std::cout << " " << std::endl; 

   orientation s;
   point p1 (10, 0), q1(0, 10),  p2 (0, 0), q2 (10, 10);
    s.doIntersect(p1, q1, p2, q2)? std::cout << "Yes\n": std::cout << "No\n";
 	std::cout << " " << std::endl; 





 return 0;
 
}
