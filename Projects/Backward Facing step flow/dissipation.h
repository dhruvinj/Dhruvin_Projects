#include<iostream>
#include<cmath>
#include<string>
#include<cassert>
#include<fstream>
#include<cstdlib>





void dissipation(int nodes, double** u, double** v, double** p, double** U, double** V, double** g_11, double** g_22, double** J, double** dis_1, double** dis_2, double** dis_3, double episilon)

{

//std::cout << "The dissipation smoothing Number = " << episilon << "\n";
  int z=3;

  double D_1[z][nodes][nodes];
  double D_2[z][nodes][nodes];
  double D_xita[z][nodes][nodes];
  double D_eta[z][nodes][nodes];



  double rho_a1[nodes][nodes];
  double rho_a2[nodes][nodes];


  for(int i = 0; i < nodes; i++)
    {
      for(int j = 0; j < nodes; j++){

	dis_1[i][j] = 0.0;
	dis_2[i][j] = 0.0;
	dis_3[i][j] = 0.0;
            
	D_1[0][i][j] = 0.0;
	D_1[1][i][j] = 0.0;
	D_1[2][i][j] = 0.0;   
         
	D_2[0][i][j] = 0.0;
	D_2[1][i][j] = 0.0;
	D_2[2][i][j] = 0.0;      
         
	D_xita[0][i][j] = 0.0;
	D_xita[1][i][j] = 0.0;
	D_xita[2][i][j] = 0.0; 
         
	D_eta[0][i][j] = 0.0;
	D_eta[1][i][j] = 0.0;
	D_eta[2][i][j] = 0.0; 
         

	rho_a1[i][j] = 0.0;
	rho_a2[i][j] = 0.0;
      }
    }

  for(int i = 0; i < nodes; i++)
    {
      for(int j = 0; j < nodes; j++){

	rho_a1[i][j]  = (abs(U[i][j]) + sqrt(pow(U[i][j],2)+ g_11[i][j]))/J[i][j];
	rho_a2[i][j]  = (abs(V[i][j]) + sqrt(pow(V[i][j],2)+ g_22[i][j]))/J[i][j];
		 
      }
    }



  for(int i = 1; i < nodes-2; i++)
    {
      for(int j = 0; j < nodes; j++){

	D_1[0][i][j] = episilon*rho_a1[i][j]*(p[i+2][j] - 3*p[i+1][j] +3*p[i][j] - p[i-1][j]);

	D_1[1][i][j] = episilon*rho_a1[i][j]*(u[i+2][j] - 3*u[i+1][j] +3*u[i][j] - u[i-1][j]);

	D_1[2][i][j] = episilon*rho_a1[i][j]*(v[i+2][j] - 3*v[i+1][j] +3*v[i][j] - v[i-1][j]);
		 
      }
    }


  for(int i = nodes-2; i < nodes-1; i++)
    {
      for(int j = 0; j < nodes; j++){

	D_1[0][i][j] = D_1[0][nodes-3][j] ;

	D_1[1][i][j] = D_1[1][nodes-3][j] ;

	D_1[2][i][j] = D_1[2][nodes-3][j] ;
		 
      }
    }



  for(int i = 0; i < nodes; i++)
    {
      for(int j = 1; j < nodes-2; j++){

	D_2[0][i][j] = episilon*rho_a2[i][j]*(p[i][j+2] - 3*p[i][j+1] +3*p[i][j] - p[i][j-1]);

	D_2[1][i][j] = episilon*rho_a2[i][j]*(u[i][j+2] - 3*u[i][j+1] +3*u[i][j] - u[i][j-1]);

	D_2[2][i][j] = episilon*rho_a2[i][j]*(v[i][j+2] - 3*v[i][j+1] +3*v[i][j] - v[i][j-1]);
		 
      }
    }

  for(int i = 0; i < nodes; i++)
    {
      for(int j = nodes-2; j < nodes-1; j++){

	D_2[0][i][j] = D_2[0][i][nodes-3];

	D_2[1][i][j] = D_2[1][i][nodes-3];

	D_2[2][i][j] = D_2[2][i][nodes-3];
		 
      }
    }

  for(int k=0; k<3;k++)
    {

      for(int i = 1; i < nodes-1; i++)
	{
	  for(int j = 0; j < nodes; j++){

	    D_xita[k][i][j] = D_1[k][i][j] - D_1[k][i-1][j];

		 
	  }
	}

    }

  for(int k=0; k<3;k++)
    {

      for(int i = 0; i < nodes; i++)
	{
	  for(int j = 1; j < nodes-1; j++){

	    D_eta[k][i][j] = D_2[k][i][j] - D_2[k][i][j-1];

		 
	  }
	}

    }



  for(int i = 1; i < nodes-2; i++)
    {
      for(int j = 1; j < nodes-2; j++){

	dis_1[i][j] = D_eta[0][i][j] +  D_xita[0][i][j];
	dis_2[i][j] = D_eta[1][i][j] +  D_xita[1][i][j];
	dis_3[i][j] = D_eta[2][i][j] +  D_xita[2][i][j];
      }
    }



}
