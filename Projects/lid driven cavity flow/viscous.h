#include<iostream>
#include<cmath>
#include<string>
#include<cassert>
#include<fstream>
#include<cstdlib>


void viscous(double** x,double** y,int nodes, double** eta, double** xita, double** G, double** J, double** xita_x, double** xita_y, double** eta_x, double** eta_y, double** x_xita, double** y_eta,double** x_eta,double** y_xita, double** u, double** v, double** p, double** U, double** V, double*** dEv1,double*** dEv2)

{
int z=3;
double Ev1[z][nodes][nodes];


double Ev2[z][nodes][nodes];

  for(int k=0;k<3;k++)
    {
    for(int i = 0; i < nodes; i++)
        {
	    for(int j = 0; j < nodes; j++){

		     Ev1[k][i][j]  = 0;
		     Ev2[k][i][j]  = 0;
             dEv1[k][i][j] = 0;
             dEv2[k][i][j] = 0;
		    }
        }
    }

double Jhp[nodes][nodes];
double xita_xhp[nodes][nodes];
double xita_yhp[nodes][nodes];
double eta_xhp[nodes][nodes];
double eta_yhp[nodes][nodes];


double Jnp[nodes][nodes];
double xita_xnp[nodes][nodes];
double xita_ynp[nodes][nodes];
double eta_xnp[nodes][nodes];
double eta_ynp[nodes][nodes];

double g_11p[nodes][nodes];
double g_12p[nodes][nodes];
double g_22p[nodes][nodes];

double g_11n[nodes][nodes];
double g_12n[nodes][nodes];
double g_22n[nodes][nodes];

double Re = 500.00;

for(int i = 0; i < nodes-1; i++)
{
	for(int j = 0; j < nodes; j++){

		Jhp[i][j] = 0.5*(J[i+1][j] + J[i][j]);
		xita_xhp[i][j] = 0.5*(xita_x[i+1][j] + xita_x[i][j]);
		xita_yhp[i][j] = 0.5*(xita_y[i+1][j] + xita_y[i][j]);
		eta_xhp[i][j] = 0.5*(eta_x[i+1][j] + eta_x[i][j]);
		eta_yhp[i][j] = 0.5*(eta_y[i+1][j] + eta_y[i][j]);
}
}


for(int i = nodes-1; i < nodes; i++)
{
	for(int j = 0; j < nodes; j++){

		Jhp[i][j] = 0.5*(J[i-1][j] + J[i][j]);
		xita_xhp[i][j] = 0.5*(xita_x[i-1][j] + xita_x[i][j]);
		xita_yhp[i][j] = 0.5*(xita_y[i-1][j] + xita_y[i][j]);
		eta_xhp[i][j] = 0.5*(eta_x[i-1][j] + eta_x[i][j]);
		eta_yhp[i][j] = 0.5*(eta_y[i-1][j] + eta_y[i][j]);
}
}


for(int i = 0; i < nodes; i++)
{
	for(int j = 0; j < nodes-1; j++){

		Jnp[i][j] = 0.5*(J[i][j+1] + J[i][j]);
		xita_xnp[i][j] = 0.5*(xita_x[i][j+1] + xita_x[i][j]);
		xita_ynp[i][j] = 0.5*(xita_y[i][j+1] + xita_y[i][j]);
		eta_xnp[i][j] = 0.5*(eta_x[i][j+1] + eta_x[i][j]);
		eta_ynp[i][j] = 0.5*(eta_y[i][j+1] + eta_y[i][j]);
}
}


for(int i = 0; i < nodes; i++)
{
	for(int j = nodes-1; j < nodes; j++){

		Jnp[i][j] = 0.5*(J[i][j-1] + J[i][j]);
		xita_xnp[i][j] = 0.5*(xita_x[i][j-1] + xita_x[i][j]);
		xita_ynp[i][j] = 0.5*(xita_y[i][j-1] + xita_y[i][j]);
		eta_xnp[i][j] = 0.5*(eta_x[i][j-1] + eta_x[i][j]);
		eta_ynp[i][j] = 0.5*(eta_y[i][j-1] + eta_y[i][j]);
}
}


for(int i = 0; i < nodes; i++)
{
	for(int j = 0; j < nodes; j++){

		g_11p[i][j] = pow(xita_xhp[i][j],2) + pow(xita_yhp[i][j],2);
		g_12p[i][j] = xita_xhp[i][j]*eta_xhp[i][j] +xita_yhp[i][j]*eta_yhp[i][j];
		g_22p[i][j] = pow(eta_xhp[i][j],2) + pow(eta_yhp[i][j],2);
		g_11n[i][j] = pow(xita_xnp[i][j],2) + pow(xita_ynp[i][j],2);
		g_12n[i][j] = xita_xnp[i][j]*eta_xnp[i][j] +xita_ynp[i][j]*eta_ynp[i][j];
		g_22n[i][j] = pow(eta_xnp[i][j],2) + pow(eta_ynp[i][j],2);

}

for(int i = 0; i < nodes-1; i++)
{
	for(int j = 0; j < nodes-1; j++){

		 Ev1[0][i][j]  = 0;
		 Ev1[1][i][j]  = (g_11p[i][j]*(u[i+1][j] - u[i][j]) + g_12p[i][j]*(u[i][j+1]-u[i][j]))/(Re*Jhp[i][j]);
		 Ev1[2][i][j]  = (g_11p[i][j]*(v[i+1][j] - v[i][j]) + g_12p[i][j]*(v[i][j+1]-v[i][j]))/(Re*Jhp[i][j]);
		}
}
for(int i = 0; i < nodes-1; i++)
{
	for(int j = 0; j < nodes-1; j++){
		 Ev2[0][i][j]  = 0;
		 Ev2[1][i][j]  = (g_12n[i][j]*(u[i+1][j] - u[i][j]) + g_22n[i][j]*(u[i][j+1]-u[i][j]))/(Re*Jnp[i][j]);
		 Ev2[2][i][j]  = (g_12n[i][j]*(v[i+1][j] - v[i][j]) + g_22n[i][j]*(v[i][j+1]-v[i][j]))/(Re*Jnp[i][j]);
		}
}



	for(int i = 1; i < nodes-1; i++)
	{
		for(int j = 1; j < nodes-1; j++){

			 dEv1[0][i][j]  = 1*(Ev1[0][i][j] - Ev1[0][i-1][j]);
             dEv1[1][i][j]  = 1*(Ev1[1][i][j] - Ev1[1][i-1][j]);
			 dEv1[2][i][j]  = 1*(Ev1[2][i][j] - Ev1[2][i-1][j]);
			 
             dEv2[0][i][j]  = 1*(Ev2[0][i][j] - Ev2[0][i][j-1]);
             dEv2[1][i][j]  = 1*(Ev2[1][i][j] - Ev2[1][i][j-1]);
			 dEv2[2][i][j]  = 1*(Ev2[2][i][j] - Ev2[2][i][j-1]);
			}
	}









}









}
