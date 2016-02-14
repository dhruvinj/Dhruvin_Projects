#include<iostream>
#include<cmath>
#include<string>
#include<cassert>
#include<fstream>
#include<cstdlib>
#include<vector>
double int_1(double dn1_dxita, double dn2_dxita, std::vector<double> x, int i );
double int_2(std::vector<double> x, int i);
double int_2(std::vector<double> x, int i, double k1);	
double shape_1(double xita)
{
  return 0.5*(1-xita);
}

double shape_2(double xita)
{
  return 0.5*(1+xita);
}


int main(int argc, char* argv[])
{
  double pi;
  pi= M_PI;


  //Number of nodes for finite element analysis
  // Number of elements is one less than nodes for linear shape function. 

  const int nodes = 21;
  const int elements = nodes-1;

  // Constructing the 1D grid

  double h;
  double dn1_dxita = -0.5;
  double dn2_dxita = 0.5;


  std::vector<double> x (nodes,0);

  h = double(pi)/double(nodes-1);

  x[0] = 0;

  for(int i=1; i< nodes; i++){
    x[i] = x[i-1] + h ;
  }


  // stiffness matrix

  std::vector< std::vector<double> > k;
  //now we have an empty 2D-matrix of size (0,0). Resizing it with one single command:
  k.resize( nodes , std::vector<double>( nodes , 0.0 ) );

  for(int i=0 ; i< elements; i++)
    {
      k[i][i]     =  -int_1(dn1_dxita,dn1_dxita,x,i) + int_2(x,i,1) + k[i][i];
      k[i][i+1]   =  -int_1(dn1_dxita,dn2_dxita,x,i) + int_2(x,i,2) ;
      k[i+1][i]   =  -int_1(dn2_dxita,dn1_dxita,x,i) + int_2(x,i,3) ;
      k[i+1][i+1] =  -int_1(dn2_dxita,dn2_dxita,x,i) + int_2(x,i,4) + k[i+1][i+1];

    }
for (int i=0; i<nodes;i++)
{
	for (int j=0;j<nodes;j++)
	{
		std::cout << k[i][j] << " ";
		

	}
std::cout << "\n";

}



  return 0;

}


double int_1(double dn1_dxita, double dn2_dxita, std::vector<double> x, int i )
{
  double sum =0.0;
  double W = 2.0;

  sum = dn1_dxita*dn2_dxita*(double(2)/(x[i+1]-x[i]))*W;

  return sum;
}


double int_2(std::vector<double> x, int i, double k1)
{
  double sum =0.0;
  double W1 = 1.0;
  double W2 = 1.0;

  if(k1 ==1)
    {
      sum = shape_1(0.57735)*shape_1(0.57735)*0.5*(x[i+1]-x[i])*W1 + shape_1(-0.57735)*shape_1(-0.57735)*0.5*(x[i+1]-x[i])*W2;
    }

  if(k1 ==2)
    {
      sum = shape_1(0.57735)*shape_2(0.57735)*0.5*(x[i+1]-x[i])*W1 + shape_1(-0.57735)*shape_2(-0.57735)*0.5*(x[i+1]-x[i])*W2;
    }

  if(k1 ==3)
    {
      sum = shape_2(0.57735)*shape_1(0.57735)*0.5*(x[i+1]-x[i])*W1 + shape_2(-0.57735)*shape_1(-0.57735)*0.5*(x[i+1]-x[i])*W2;
    }

  if(k1 ==4)
    {
      sum = shape_2(0.57735)*shape_2(0.57735)*0.5*(x[i+1]-x[i])*W1 + shape_2(-0.57735)*shape_2(-0.57735)*0.5*(x[i+1]-x[i])*W2;
    }

  return sum; 

}

