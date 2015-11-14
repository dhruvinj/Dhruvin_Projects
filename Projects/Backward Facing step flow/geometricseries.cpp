#include<iostream>
#include<cmath>
#include<string>
#include<cassert>
#include<fstream>
#include<cstdlib>

void tdma(int ibeg , int iend, double* aa, double* bb, double* cc, double* dd);
int main(int argc, char* argv[])
{
  int nodes,Nmx, Nex;
  nodes =61; 

  Nmx = double(nodes)/double(2) +0.5;
  Nex = nodes - Nmx;

  double r=1.1;
  double a1;


  double a = 5*(1-r)/(1- pow(r,Nmx-1));

  //std::cout << a << "\n";

  double x1[nodes], y1[nodes];
  for(int i=0; i< nodes ; i++)
    {
      x1[i] = 0;
    }
  x1[0] =0;
  x1[1] = a;

  for(int i=2; i< Nmx ; i++)
    {
      x1[i] = x1[i-1] + a*pow(r,i-1);
    }
  double b = -5*(1-r)/(1- pow(r,Nex-1));

  x1[nodes-1] = 10;
  x1[nodes-2] = 10+b;

  for(int i = 2 ; i< Nex; i++)
    {
      x1[nodes-1-i] = x1[nodes-i] + b*pow(r,i-2);
    }




  double c = 0.5*(1-r)/(1- pow(r,Nmx-1));

  y1[0] =0;
  y1[1] = c;

  for(int i=2; i< Nmx ; i++)
    {
      y1[i] = y1[i-1] + c*pow(r,i-1);
    }
  double d = -0.5*(1-r)/(1- pow(r,Nex-1));

  y1[nodes-1] = 1;
  y1[nodes-2] = 1+d;

  for(int i = 2 ; i< Nex; i++)
    {
      y1[nodes-1-i] = y1[nodes-i] + d*pow(r,i-2);
    }




  return 0;
}
