#include<iostream>
#include<cmath>
#include<string>
#include<cassert>
#include<fstream>
#include<cstdlib>


void bcsuv(int nodes, double** u,double** v,double** p)

{




for (int i=0; i< nodes; i++)
{
for(int j=0; j< nodes; j++){
u[i][j] = 0.0;
v[i][j] = 0.0;
p[i][j] = 0.0; 
}
}


for (int i=nodes-1; i< nodes; i++)
{
for(int j=0; j< nodes; j++){
u[i][j] = 1.0;
}
}
/*
for (int i=0; i<nodes;i++)
{
	for (int j=0;j<nodes;j++)
	{
		std::cout << v[i][j];
		

	}
std::cout << "\n";

}
*/
}








