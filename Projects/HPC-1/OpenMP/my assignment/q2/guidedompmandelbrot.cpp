#include<iostream>
#include<cmath>
#include<string>
#include<cassert>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include "ComplexNumber.hpp"
#include<omp.h>


 int main(int argc, char* argv[])
 {
 
 long double hx;
 

int nodes[] = {1000, 2000,3000, 5000, 8000, 12000};
  int nthreads,chunksize ; 
  chunksize = 100; 
 
  double ctime1;
  double ctime2;
  int g = sizeof(nodes)/sizeof(nodes[0]);
   double time[g]; 
  for(int h=0; h< g ; h++)
  {
 double* x;
 x = new double[nodes[h]];

 double** Creal;
 double** Cimag;
 
 Creal = new double*[nodes[h]];
 Cimag = new double*[nodes[h]];
 
 for(int i = 0; i < nodes[h]; i++)
  {
 	Creal[i] = new double[nodes[h]];
  Cimag[i] = new double[nodes[h]];
  }

 hx = double(4)/double(nodes[h]-1);

 x[0]=-2;
 for(int i=1;i< nodes[h];i++)
 	{
 	x[i] = x[i-1] + hx;
 	}
 	
 	for(int i = 0; i < nodes[h]; i++)
  {
   for(int j = 0; j < nodes[h]; j++){

    Creal[i][j] = x[j];
    Cimag[i][j] = x[i]; 
    }
  }
  
 double real = 0.0;
 double imag = 0.0;
 double sum = 0.0;
	int a = 0;
	int b = 0;
	int i,j;
omp_set_num_threads(24); 
ctime1 = omp_get_wtime();

#pragma omp parallel for private(i) reduction(+:sum) schedule(guided, 100)
 for(int i=0; i< nodes[h]*nodes[h] ;i++)
 {
  real = Creal[i/nodes[h]][i%nodes[h]];
  imag = Cimag[i/nodes[h]][i%nodes[h]];
 
 ComplexNumber z1;
 ComplexNumber cstart(real, imag);
 ComplexNumber z0;
 for(int j=0; j< 10000; j++)
 {
 	z1 = z0.CalculatePower(2) + cstart;
 	
 	if(z1.CalculateModulus() > 2)
 	{
 	break;
 	}
 	else if( j == (10000 -1))
 	{
 	sum += hx*hx;
 	}
  z0 = z1 ; 
 }

 }


 std::cout << sum << "\n";
 ctime2 = omp_get_wtime();

 time[h] = (ctime2-ctime1); 

 std::cout << time[h] << std::endl;

 
 delete[] x;

 
 for(int i = 0; i < nodes[h]; i++)
  {
 	delete[] Creal[i];
  delete[] Cimag[i];
  }
 	delete[] Creal;
  delete[] Cimag;
 
 }
 return 0;
 }
