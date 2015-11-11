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
 
 std::string program_name = argv[0];
 unsigned long int number_of_nodes = atoi(argv[1]);
 int t = atof(argv[2]);
 char* file_name = argv[3];

unsigned long int nodes = number_of_nodes;


  double ctime1;
  double ctime2;

   double time; 
 
 double* x;
 x = new double[nodes];

 double** Creal;
 double** Cimag;
 
 Creal = new double*[nodes];
 Cimag = new double*[nodes];
 
 for(int i = 0; i < nodes; i++)
  {
 	Creal[i] = new double[nodes];
  Cimag[i] = new double[nodes];
  }

 hx = double(4)/double(nodes-1);

 x[0]=-2;
 for(int i=1;i< nodes;i++)
 	{
 	x[i] = x[i-1] + hx;
 	}
 	
 	for(int i = 0; i < nodes; i++)
  {
   for(int j = 0; j < nodes; j++){

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

 sum =0.0;
omp_set_num_threads(t); 
ctime1 = omp_get_wtime();

#pragma omp parallel for private(i) reduction(+:sum) schedule(guided, 10)
 for(int i=0; i< nodes*nodes ;i++)
 {
  real = Creal[i/nodes][i%nodes];
  imag = Cimag[i/nodes][i%nodes];
 
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

 time = (ctime2-ctime1); 

std::cout << time << std::endl;



 
std::ofstream write_file(file_name);
// Write numbers as +x.<13digits>e+00 (width 20)
write_file.setf(std::ios::scientific);
write_file.precision(30);

assert(write_file.is_open());

write_file << time << std::endl;

write_file.close();
 
 delete[] x;

 
 for(int i = 0; i < nodes; i++)
  {
 	delete[] Creal[i];
  delete[] Cimag[i];
  }
 	delete[] Creal;
  delete[] Cimag;
 
 return 0;
 }
