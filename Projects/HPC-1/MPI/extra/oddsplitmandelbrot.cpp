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
	 int nodes[] = {5};

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
    //first half of the grid done

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
 std::cout << "====================================================" << std::endl ;
  
 for(int i= 0; i< rows ; i++)
  {
  	for(int j=0; j < cols ; j++)
  		{
  		
  		std::cout << Creal[i][j] << " ";
  		
  		}
  std::cout << "\n";
  }
  
  std::cout << "====================================================" << std::endl ;
  
 for(int i= 0; i< rows ; i++)
  {
  	for(int j=0; j < cols ; j++)
  		{
  		
  		std::cout << Cimag[i][j] << " ";
  		
  		}
  std::cout << "\n";
  }
 
 
 std::cout << "====================================================" << std::endl ;
 
 	
 	int istart, iend ;
 		istart = ((nodes[0]*(nodes[0]/2))/4)*1;
    iend   = ((nodes[0]*(nodes[0]/2))/4)*1 + nodes[0];
    
    

 double real, imag;
 for(int i=istart; i < iend ;i++)
 {
  int a = i/(nodes[0]);
  int b = i%(nodes[0]);
  real = Creal[a][b];
  imag = Cimag[a][b];

std::cout << real << "         " << imag << std::endl;
}
 
 
 /*
 hx = double(4)/double(nodes[0]-1);
 hy = double(4)/double(nodes[0]-1);
 x[0]=-2;
 y[0] = 0 ;
 for(int i=1;i< nodes[0];i++)
 	{
 	x[i] = x[i-1] + hx;
 	}
  
  for(int i=1; i < nodes[0]/2 ;i++)
 	{
 	y[i] = y[i-1] + hy;
 	}
 	
 	for(int i=0; i < nodes[0]/2 ;i++)
 	{
 	std::cout << y[i] <<std::endl;
 	}
 	
 	
 	
 	for(int i= 0; i< rows ; i++)
  {
  	for(int j=0; j < cols ; j++)
  		{
  		
  		Creal[i][j] = x[j];
  		Cimag[i][j] = y[i];
  		}
  
  }
  

 
   
   int istart, iend ;
 		istart = ((nodes[0]*(nodes[0]/2))/2)*0;
    iend   = ((nodes[0]*(nodes[0]/2))/2)*0 + nodes[0];
    
   
   	double real, imag;
 for(int i=istart; i < iend ;i++)
 {
  int a = i/(nodes[0]);
  int b = i%(nodes[0]);
  real = Creal[a][b];
  imag = Cimag[a][b];
std::cout << real << "         " << imag << std::endl;
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
