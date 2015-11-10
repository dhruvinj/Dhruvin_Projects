#include<iostream>
#include<cmath>
#include<string>
#include<cassert>
#include<fstream>
#include<cstdlib>

void gridgeneration(int nodes, double r,double** x,double** y,double* dx)
{

  int nm = double(nodes)/double(2) + 0.5;
  int ne = nodes - nm;

 
  if (r==1)
    {
      *dx = 1./double(nodes-1); 
      double x1[nodes], y1[nodes];	
      x1[0] =0.0;
      y1[0] =0.0;
      for(int i=1; i< nodes; i++){
	x1[i] = x1[i-1] + *dx ;
	y1[i] = y1[i-1] + *dx;
      }
      for(int i = 0; i < nodes; i++)
	{
	  for(int j = 0; j < nodes; j++){

	    x[i][j] = x1[j];
	    y[i][j] = y1[i];
	  }
	}

      //std::cout << *dx << "\n";
    }
}
