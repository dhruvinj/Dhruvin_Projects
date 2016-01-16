#include<iostream>
#include<cmath>
#include<math.h>
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
	//	std::cout << "The CFL Number = "<< CFL << "\n";
  //  std::cout << "The Von Neumann Number = " << VN << "\n";

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

	rho_a1[i][j]  = (std::abs(U[i][j]) + sqrt(pow(U[i][j],2)+ g_11[i][j]))/J[i][j];
	rho_a2[i][j]  = (std::abs(V[i][j]) + sqrt(pow(V[i][j],2)+ g_22[i][j]))/J[i][j];
		 
      }
    }
	double a;
	double b;
  for(int i = 0; i < nodes; i++)
    {
      for(int j = 0; j < nodes; j++){

	// a = maximum(rho_a1[i][j],rho_a2[i][j]);
	// b = maximum(g_11[i][j],g_22[i][j]);
	dt1[i][j]  = double (CFL)/double(maximum(rho_a1[i][j],rho_a2[i][j]));
	dt2[i][j]  = double (Re*VN)/ double(maximum(g_11[i][j],g_22[i][j]));
      }
    }


  for(int i = 0; i < nodes; i++)
    {
      for(int j = 0; j < nodes; j++){

         
	//dt[i][j] = minimum(dt1[i][j],dt2[i][j]);

    dt[i][j] = 0.001;
      }
    }


}

