#include<iostream>
#include<cmath>
#include<string>
#include<cassert>
#include<fstream>
#include<cstdlib>

double minimum(double a, double b)
{
  double min;

  if (a <= b)
    {
      min = a;
    }
  else
    {
      min = b;
    }
  return min;
}
