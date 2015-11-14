#include<iostream>
#include<cmath>
#include<string>
#include<cassert>
#include<fstream>
#include<cstdlib>


void bcsuv(int nodes, double** u,double** v,double** p)

{

  double y1[nodes];
  double dy;
  dy = 1./double(nodes-1);
	
  y1[0] =0.0;
  for(int i=1; i< nodes; i++){
    y1[i] = y1[i-1] + dy;
  }



  for (int i=0; i< nodes; i++)
    {
      for(int j=0; j< nodes; j++){
	u[i][j] = 0.0;
	v[i][j] = 0.0;
	p[i][j] = 0.0; 
      }
    }


  for (int i=0; i< nodes; i++)
    {
      for(int j=0; j< 1; j++){
	if(y1[i] < 0.5)
	  {
	    u[i][j] = 0.0;
	  }
	else
	  {
	    u[i][j] = (double(1)/double(0.0625)) * ((y1[i]-0.5)*(1-y1[i]));
	  }
      }
    }

  u[nodes-1][0] = 0.0;
  /*
    for (int i=0; i<nodes;i++)
    {
    for (int j=0;j<nodes;j++)
    {
    std::cout << u[i][j];
		

    }
    std::cout << "\n";

    }
  */
}








