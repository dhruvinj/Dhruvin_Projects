#include<iostream>
#include<cmath>
#include<string>
#include<cassert>
#include<fstream>
#include<cstdlib>

double maximum(double a, double b)
{
  double max;

  if (a <= b)
    {
      max = b;
    }
  else
    {
      max = a;
    }
  return max;
}
