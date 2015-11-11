#include<iostream>
#include<cmath>
#include<string>
#include<cassert>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include "ComplexNumber.hpp"
#include<mpi.h>
#include<sstream>
int main(int argc, char* argv[])
{

  double hx,hy;

  int number_of_nodes = atoi(argv[1]);


  //unsigned long int nodes = number_of_nodes;

  int nodes[] = {number_of_nodes};
  
  unsigned int r;
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

 
      hy = double(4)/double(nodes[h]-1);
      x[0]=-2;
      y[0] = -2;
      for(int i=1;i< nodes[h];i++)
 	{
	  x[i] = x[i-1] + hy;
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

      unsigned long int istart, iend;
      int nproc, myrank, ierr;
 
      double  hx,sum, total_sum, area;
      double time2, time1;
   
      MPI_Init(&argc,&argv);
      MPI_Comm_size(MPI_COMM_WORLD, &nproc);
      MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    
      if(myrank == 0) {
	std::cout << "MPI version with tasks =" <<  nproc << std::endl;
	std::cout << "Number of intervals:" <<  nodes[0] << std::endl;
      }
      if (r = (nodes[0]*nodes[0]) % nproc) {
	if(myrank == 0) {
	  std::cout << "The number of process must divide exactly " << nodes[0] << std::endl;
          MPI_Finalize();
          return 1;
	}  
      }
    
      time1 = MPI_Wtime();
      istart = ((nodes[0]*nodes[0])/nproc)*myrank ;
      iend   = ((nodes[0]*nodes[0])/nproc)*(myrank+1);
      sum = 0.0;
      total_sum = 0.0;
    
      hx = double(4)/double(nodes[h]-1);
 
      for(int i=istart; i < iend ;i++)
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
		  sum += hx*hx;
		}
	      z0 = z1 ; 
	    }

	}
 
      ierr=MPI_Reduce(&sum,&total_sum,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
      time2 = MPI_Wtime(); 
 		 
      area = total_sum;
 		 
 		 
      if(myrank == 0) {
	std::cout << "Computed Area  " << area << std::endl;
      
	std::cout << "Elapsed time (s) = " << time2-time1 << std::endl ;
      }

      MPI_Finalize();

     
      if(myrank == 0) {
	std::cout << "MPI version with tasks =" <<  nproc << std::endl;
	std::cout << "Number of intervals:" <<  nodes[0] << std::endl;
       
	std::string file = "nproc"; 
       
	std::ofstream piestimate;
	std::stringstream process;
	process << nproc;
	
	std::string filename = "mandelbrot"+process.str()+".dat";
	
	
	piestimate.open(filename.c_str() );
	
	piestimate << nproc ;
	
	piestimate.close();
    
	process.str("");
      
      
         
	std::ofstream timeval;
	std::stringstream process1;
	process1 << nproc;
	
	std::string filename1 = "timeval"+process1.str()+".dat";
	
	
	timeval.open(filename1.c_str() );
	
	timeval << time2 ;
	
	timeval.close();
    
	process1.str("");
       
      }

      /*
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
      */
 
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
