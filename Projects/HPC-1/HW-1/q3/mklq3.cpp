#include<iostream>
#include<cmath>
#include<string>
#include<cassert>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<mkl.h>
int main(int argc, char* argv[])
{

  int nodes[] = {2000000, 4000000,6000000,8000000,10000000};
  int k = sizeof(nodes)/sizeof(nodes[0]);

  double msecs[k];

  clock_t start, end;
  //std::cout << nodes <<"\n";
  int a=0;
  for(int z=0; z < k; z++)
    {

      double dotproduct=0.0;

      double* A = new double [nodes[z]];
      double* B = new double [nodes[z]];
      int len = nodes[z];
      int incm = 1, incn = 1;

      for(int i = 0; i< nodes[z]; i++)
	{

	  A[i] = 1;
	  B[i] = 2;

	}
      start = clock();
    
      dotproduct = cblas_ddot(len, A, incm, B, incn);

      end = clock();
      msecs[a] =  ((double) (end - start)) * 1000 / CLOCKS_PER_SEC ;
      std::cout << msecs[a] <<"\n";
      std::cout << dotproduct <<"\n";
      a=a+1;

      delete[] A ;
      delete[] B ;



    }

  std::ofstream write_file("mkl.dat");
  // Write numbers as +x.<13digits>e+00 (width 20)
  write_file.setf(std::ios::scientific);
  write_file.precision(30);

  assert(write_file.is_open());
  for (int i=0; i< 5; i++)
    {

      write_file << msecs[i] << "\n";

    }
  write_file.close();

  std::ofstream write_v("nodes.dat");
  // Write numbers as +x.<13digits>e+00 (width 20)
  write_v.setf(std::ios::scientific);
  write_v.precision(30);

  assert(write_v.is_open());
  for (int i=0; i< 5; i++)
    {

      write_v << nodes[i] <<  "\n"; 

    }
  write_v.close();


  return 0;
}
