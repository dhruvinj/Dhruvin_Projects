#include<iostream>
#include<cmath>
#include<string>
#include<cassert>
#include<fstream>
#include<cstdlib>

void gridgeneration(int nodes, double r,double** x,double** y,double* dx,double* dy)
{

  double x1[nodes], y1[nodes];

  int nm = double(nodes)/double(2) + 0.5;
  int ne = nodes - nm;

 
  if (r==1.0)
    {
      *dx = 10./double(nodes-1); 
      *dy = 1./double(nodes-1);
	
      x1[0] =0.0;
      y1[0] =0.0;
      for(int i=1; i< nodes; i++){
	x1[i] = x1[i-1] + *dx ;
	y1[i] = y1[i-1] + *dy;
      }


      //std::cout << *dx << "\n";
    }

  else
    {
      int Nmx,Nex;
      Nmx = double(nodes)/double(2) +0.5;
      Nex = nodes - Nmx;

      double a = 5*(1-r)/(1- pow(r,Nmx-1));

      //std::cout << a << "\n";

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






    }


  for(int i = 0; i < nodes; i++)
    {
      for(int j = 0; j < nodes; j++){

	x[i][j] = x1[j];
	y[i][j] = y1[i];
      }
    }


}
