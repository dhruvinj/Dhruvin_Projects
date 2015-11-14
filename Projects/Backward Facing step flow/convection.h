#include<iostream>
#include<cmath>
#include<string>
#include<cassert>
#include<fstream>
#include<cstdlib>

void convection(double** x,double** y,int nodes, double** eta, double** xita, double** G, double** J, double** xita_x, double** xita_y, double** eta_x, double** eta_y, double** x_xita, double** y_eta,double** x_eta,double** y_xita, double** u, double** v, double** p, double** U, double** V, double** g_11, double** g_12, double** g_22, double*** dEs1,double*** dEs2)

{
  int z=3;
  double Es1[z][nodes][nodes];

  double Es2[z][nodes][nodes];
  
  for(int k=0;k<3;k++)
    {
      for(int i = 0; i < nodes; i++)
        {
	  for(int j = 0; j < nodes; j++){

	    Es1[k][i][j]  = 0;
	    Es2[k][i][j]  = 0;
	    dEs2[k][i][j]  = 0;
	    dEs2[k][i][j]  = 0;
	  }
        }
    }

  for(int i = 0; i < nodes; i++)
    {
      for(int j = 0; j < nodes; j++){

	U[i][j] = (u[i][j]*xita_x[i][j] + v[i][j]*xita_y[i][j]);
	V[i][j] = (u[i][j]*eta_x[i][j] + v[i][j]*eta_y[i][j]);
      }
    }
  /*
    for (int i=0; i<nodes;i++)
    {
    for (int j=0;j<nodes;j++)
    {
    std::cout << U[i][j];
		

    }
    std::cout << "\n";

    }
  */

  for(int i = 0; i < nodes; i++)
    {
      for(int j = 0; j < nodes; j++){

	Es1[0][i][j]  = U[i][j]/J[i][j];
	Es1[1][i][j]  = (u[i][j]*U[i][j] + p[i][j]*xita_x[i][j])/J[i][j];
	Es1[2][i][j]  = (v[i][j]*U[i][j] + p[i][j]*xita_y[i][j])/J[i][j];
		
	Es2[0][i][j]  = V[i][j]/J[i][j];
	Es2[1][i][j]  = (u[i][j]*V[i][j] + p[i][j]*eta_x[i][j])/J[i][j];
	Es2[2][i][j]  = (v[i][j]*V[i][j] + p[i][j]*eta_y[i][j])/J[i][j];
      }
    }

  for(int k =0 ; k< 3 ;k++)
    {
      for(int i = 1; i < nodes-1; i++)
	{
	  for(int j = 1; j < nodes-1; j++){

	    dEs1[k][i][j]  = 0.5*(Es1[k][i+1][j] - Es1[k][i-1][j]);
			 
	    dEs2[k][i][j]  = 0.5*(Es2[k][i][j+1] - Es2[k][i][j-1]);
			
	  }
	}

    }


  for(int i = 0; i < nodes; i++)
    {
      for(int j = 0; j < nodes; j++){

	g_11[i][j]  = pow(xita_x[i][j],2) + pow(xita_y[i][j],2);
	g_12[i][j]  = xita_x[i][j]*eta_x[i][j] +xita_y[i][j]*eta_y[i][j];
	g_22[i][j]  = pow(eta_x[i][j],2) + pow(eta_y[i][j],2);
		 
		
      }
    }

  /*
    for (int i=0; i<nodes;i++)
    {
    for (int j=0;j<nodes;j++)
    {
    std::cout << g_22[i][j];
		

    }
    std::cout << "\n";

    }

  */




}
