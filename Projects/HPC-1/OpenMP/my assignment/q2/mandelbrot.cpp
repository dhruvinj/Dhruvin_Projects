#include<iostream>
#include<cmath>
#include<string>
#include<cassert>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include "ComplexNumber.hpp"


 int main(int argc, char* argv[])
 {
 
 double hx,hy;
 
  int nodes[] = { 1200};
 // int nodes[] = {500};
  int g = sizeof(nodes)/sizeof(nodes[0]);
  double elapsed_time[g];
   timespec start, end;
  for(int h=0; h< g ; h++)
  {
  
   
 double* x;
 double* y;
 double* C;
 x = new double[nodes[h]];
 y = new double[nodes[h]];
 C = new double[nodes[h]*nodes[h]];
 
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
 hy = double(4)/double(nodes[h]-1);
 x[0]=-2;
 y[0] = -2;
 for(int i=1;i< nodes[h];i++)
 	{
 	x[i] = x[i-1] + hx;
 	y[i] = y[i-1] + hy;
 	}
 	
 	for(int i = 0; i < nodes[h]; i++)
  {
   for(int j = 0; j < nodes[h]; j++){

    Creal[i][j] = x[j];
    Cimag[i][j] = y[i]; 
    }
  }
  


 	for(int i = 0; i < nodes[h]; i++)
  {
   for(int j = 0; j < nodes[h]; j++){

    C[i*nodes[h]+j] = Creal[i][j]; 
    }
  }
 double real = 0.0;
 double imag = 0.0;
 double sum = 0.0;
 
 clock_gettime(CLOCK_REALTIME,&start);
 
 for(int i=0; i< nodes[h]*nodes[h] ;i++)
 {
  int a = i/nodes[h];
  int b = i%nodes[h];
  real = Creal[a][b];
  imag = Cimag[a][b];
 
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
 	sum += hx*hy;
 	}
  z0 = z1 ; 
 }

 }
 
 clock_gettime(CLOCK_REALTIME,&end);
 
 elapsed_time[h] = 1 * (end.tv_sec - start.tv_sec) + 1e-9*(end.tv_nsec - start.tv_nsec);
 
 std::cout << elapsed_time[h] << std::endl;
   std::cout << sum << "\n";
  
   std::ofstream write_file("nonparallel.dat");
// Write numbers as +x.<13digits>e+00 (width 20)
write_file.setf(std::ios::scientific);
write_file.precision(30);

assert(write_file.is_open());
for (int i=0; i< 1; i++)
{

write_file << elapsed_time[i] << "\n";

}
write_file.close();

 
 delete[] x;
 delete[] y;
 delete[] C;
 
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
