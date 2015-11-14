#include<iostream>
#include<cmath>
#include<string>
#include<cassert>
#include<fstream>
#include<cstdlib>
#include "maximum.h"
#include "minimum.h"


double minimum(double a, double b);
double maximum(double a, double b);

void localtime(int nodes, double** U, double** V, double** g_11, double** g_22, double** J, double** dt,double Re, double CFL, double VN)
{


  double rho_a1[nodes][nodes];
  double rho_a2[nodes][nodes];

  double dt2[nodes][nodes];
  double dt1[nodes][nodes];



  for(int i = 0; i < nodes; i++)
    {
      for(int j = 0; j < nodes; j++){

	rho_a1[i][j] = 0.0;
	rho_a2[i][j] = 0.0;
	dt1[i][j] =0.0;
	dt2[i][j] =0.0;
	dt[i][j] =0.0;
      }
    }
  for(int i = 0; i < nodes; i++)
    {
      for(int j = 0; j < nodes; j++){

	rho_a1[i][j]  = (abs(U[i][j]) + sqrt(pow(U[i][j],2)+ g_11[i][j]))/J[i][j];
	rho_a2[i][j]  = (abs(V[i][j]) + sqrt(pow(V[i][j],2)+ g_22[i][j]))/J[i][j];
		 
      }
    }


  for(int i = 0; i < nodes; i++)
    {
      for(int j = 0; j < nodes; j++){

	double a = maximum(rho_a1[i][j],rho_a2[i][j]);
	double b = maximum(g_11[i][j],g_22[i][j]);
	dt1[i][j]  = CFL/a;
	dt2[i][j]  = (Re*VN)/b;
      }
    }


  for(int i = 0; i < nodes; i++)
    {
      for(int j = 0; j < nodes; j++){

         
	dt[i][j] = minimum(dt1[i][j],dt2[i][j]);
      }
    }


}

