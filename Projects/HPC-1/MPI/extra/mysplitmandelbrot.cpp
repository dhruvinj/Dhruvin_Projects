#include<iostream>
#include<cmath>
#include<string>
#include<cassert>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include "ComplexNumber.hpp"
//#include<mpi.h>
int main(int argc, char* argv[])
{
 
  int nodes[] = {4};
  
  double hx;
  double hy;
  double  sum = 0.0;
  double  total_sum = 0.0;
  double* x;
  double* y;
  double* C;
  x = new double[nodes[0]];
  y = new double[nodes[0]/2];

 
  double** Creal;
  double** Cimag;
  int rows = nodes[0]/2, cols = nodes[0];
  Creal = new double*[rows];
  Cimag = new double*[nodes[0]/2];
 
  for(int i = 0; i < rows; i++)
    {
      Creal[i] = new double[cols];
      Cimag[i] = new double[cols];
    }
    

  
  hx = double(4)/double(nodes[0]-1);
  hy = double(4)/double(nodes[0]-1);
  x[0]=-2;
  y[0] = -2;
  for(int i=1;i< nodes[0];i++)
    {
      x[i] = x[i-1] + hx;
    }
  
  for(int i=1;i< nodes[0]/2;i++)
    {
      y[i] = y[i-1] + hy;
    }
 	
  for(int i= 0; i< rows ; i++)
    {
      for(int j=0; j < cols ; j++)
	{
  		
	  Creal[i][j] = x[j];
	  Cimag[i][j] = y[i];
	}
  
    }
  
  
  /*
    for(int i= 0; i< rows ; i++)
    {
    for(int j=0; j < cols ; j++)
    {
  		
    std::cout << Creal[i][j] << " ";
  		
    }
    std::cout << "\n";
    }
 
  */
 	

 	
 
 	
  delete[] x;
  delete[] y;

  
  for (int i=0; i<rows; i++)
    {
      delete[] Creal[i];
    }
  delete[]  Creal;
  
  
  

  
  
  
  
  return 0;
}
