#include<iostream>
#include<cmath>
#include<string>
#include<cassert>
#include<fstream>
#include<cstdlib>
#include<ctime>

int main(int argc, char* argv[])
{

  int nodes[] = {100, 1000, 10000, 15000 , 20000};
  int k = sizeof(nodes)/sizeof(nodes[0]);

  double msecs[k];

  clock_t start, end;
  //std::cout << nodes <<"\n";
  int a=0;
  for(int z=0; z < k; z++)
    {

      double** A;
      double** B;
      double** C;

      A = new double* [nodes[z]];
      B = new double* [nodes[z]];
      C = new double* [nodes[z]];

      for (int i=0; i<nodes[z]; i++)
	{
	  A[i] = new double [nodes[z]];
	  B[i] = new double [nodes[z]];
	  C[i] = new double [nodes[z]];

	}
      /*
	for(int i = 0; i< nodes[z]; i++)
	{
        for(int j=0;j<nodes[z];j++)
        {
        A[i][j] = 0;
        B[i][j] = 0;
        C[i][j] = 0;
        }
	}
      */

      for(int i = 0; i< nodes[z]; i++)
	{
	  for(int j=0;j<nodes[z];j++)
	    {
	      A[i][j] = 1;
	      B[i][j] = 2;
	    }
	}
      start = clock();
      for(int j = 0; j< nodes[z]; j++)
	{
	  for(int i=0;i<nodes[z];i++)
	    {
	      C[i][j] = A[i][j] + B[i][j];
        
	    }
	}
      end = clock();
      msecs[a] =  ((double) (end - start)) * 1000 / CLOCKS_PER_SEC ;
      std::cout << msecs[a] <<"\n";
      a=a+1;

      for (int i=0; i<nodes[z]; i++)
	{
	  delete[] A[i] ;
	  delete[] B[i] ;
	  delete[] C[i] ;
	}

      delete[] A ;
      delete[] B ;
      delete[] C ;


    }



  return 0;
}
