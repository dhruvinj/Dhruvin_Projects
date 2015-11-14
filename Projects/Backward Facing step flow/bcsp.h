#include<iostream>
#include<cmath>
#include<string>
#include<cassert>
#include<fstream>
#include<cstdlib>


void bcsp(int nodes, double** p,double** u,double** v)

{

  int Nm = double(nodes)/double(2) + 0.5;
  //std::cout << Nm << "\n";
  double p_ref;

  for (int i=0; i< nodes; i++)
    {
      for(int j=nodes-1; j< nodes; j++){

	p[i][j] = 2*p[i][j-1] - p[i][j-2] ; 
      }
    }

  for (int i=0; i< nodes; i++)
    {
      for(int j=0; j< 1; j++){

	p[i][j] = 2*p[i][j+1] - p[i][j+2] ; 
      }
    }

  for (int i=0; i< 1; i++)
    {
      for(int j=1; j< nodes-1; j++){

	p[i][j] = 2*p[i+1][j] - p[i+2][j] ; 
      }
    }

  for (int i=nodes-1; i< nodes; i++)
    {
      for(int j=1; j< nodes-1; j++){

	p[i][j] = 2*p[i-1][j] - p[i-2][j] ; 
      }
    }
  p_ref = p[Nm][Nm];



  for (int i=0; i< nodes; i++)
    {
      for(int j=0; j< nodes; j++){

	p[i][j] = p[i][j] - p_ref ; 
      }
    }

  for(int i= nodes-1; i<nodes;i++)
    {
      for(int j = 0; j< nodes; j++){
	u[i][j] = u[i-1][j];
	v[i][j] = v[i-1][j];

      }


    }

}



