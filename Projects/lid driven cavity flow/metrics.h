#include<iostream>
#include<cmath>
#include<string>
#include<cassert>
#include<fstream>
#include<cstdlib>


void metrics(double** x,double** y,int nodes, double** eta, double** xita, double** G, double** J, double** xita_x, double** xita_y, double** eta_x, double** eta_y, double** x_xita, double** y_eta, double** x_eta, double** y_xita)
{

double delta_xita = 1;

double xi[nodes];
double eta1[nodes];
xi[0] = 0.0;
eta1[0] =0.0;
for(int i=1; i< nodes; i++){
xi[i] = xi[i-1] + delta_xita ;
eta1[i] = eta1[i-1] + delta_xita;
}

for(int i = 0; i < nodes; i++)
{
for(int j = 0; j < nodes; j++){

xita[i][j] = xi[j];
eta[i][j] = eta1[i];
}
}
/*
for (int i=0; i<nodes;i++)
{
	for (int j=0;j<nodes;j++)
	{
		std::cout << eta[i][j];
		

	}
std::cout << "\n";

*/
// all x_xita and y_xita
for(int i = 1; i < nodes-1; i++)
{
for(int j = 0; j < nodes; j++){

x_xita[i][j] = 0.5*(x[i+1][j] - x[i-1][j]);
y_xita[i][j] = 0.5*(y[i+1][j] - y[i-1][j]);
}
}


for(int i = 0; i < 1; i++)
{
for(int j = 0; j < nodes; j++){

x_xita[i][j] = (x[i+1][j] - x[i][j]);
y_xita[i][j] = (y[i+1][j] - y[i][j]);
}
}

for(int i = nodes-1; i < nodes; i++)
{
for(int j = 0; j < nodes; j++){

x_xita[i][j] = (x[i][j] - x[i-1][j]);
y_xita[i][j] = (y[i][j] - y[i-1][j]);
}
}

// all y_eta and x_eta

for(int i = 0; i < nodes; i++)
{
for(int j = 1; j < nodes-1; j++){

y_eta[i][j] = 0.5*(y[i][j+1] - y[i][j-1]);
x_eta[i][j] = 0.5*(x[i][j+1] - x[i][j-1]);
}
}


for(int i = 0; i < nodes; i++)
{
for(int j = 0; j < 1; j++){

y_eta[i][j] = (y[i][j+1] - y[i][j]);
x_eta[i][j] = (x[i][j+1] - x[i][j]);
}
}

for(int i = 0; i < nodes; i++)
{
for(int j = nodes-1; j < nodes; j++){

y_eta[i][j] = (y[i][j] - y[i][j-1]);
x_eta[i][j] = (x[i][j] - x[i][j-1]);
}
}


for(int i = 0; i < nodes; i++)
{
	for(int j = 0; j < nodes; j++){

		G[i][j] = x_xita[i][j]*y_eta[i][j] - x_eta[i][j]*y_xita[i][j];
		}
}

for(int i = 0; i < nodes; i++)
{
	for(int j = 0; j < nodes; j++){

		J[i][j] = double(1)/G[i][j];
		}
}


for(int i = 0; i < nodes; i++)
{
	for(int j = 0; j < nodes; j++){

		xita_x[i][j] = y_eta[i][j]/G[i][j];
		eta_x[i][j] = -y_xita[i][j]/G[i][j];
		xita_y[i][j] = -x_eta[i][j]/G[i][j];
		eta_y[i][j] = x_xita[i][j]/G[i][j];
		}
}


}

