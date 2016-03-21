#ifndef POINTDEF
#define POINTDEF

#include<iostream>

class point
{
 protected:
 

 public:
  // Constructor
  int x;
  int y;
  point() 
	:x(0), y(0)
    {
    }

  point(int a, int b)
	: x(a),y(b)
  {

  }



};
#endif
