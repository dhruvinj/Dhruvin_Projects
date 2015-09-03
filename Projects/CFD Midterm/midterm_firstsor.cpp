#include<iostream>
#include<cmath>
#include<string>
#include<cassert>
#include<fstream>
#include<cstdlib>

int main(int argc, char* argv[])

{

double pi;
pi= M_PI;


double delta_x, delta_y;
int nodes,r;
nodes = 50;
delta_x = double(2*pi)/double(nodes-1);
delta_y = double(2)/double(nodes-1);
double w = 1.68;
double x[nodes], y[nodes];	
double analytical[nodes][nodes];
double pold[nodes][nodes];
double pnew[nodes][nodes];
double psor[nodes][nodes];
double perr[nodes][nodes];
double u[nodes][nodes];
double v[nodes][nodes];
double err;
for(int i = 0; i < nodes; i++)
{
	for(int j = 0; j < nodes; j++){

	pold[i][j] = 0.0;
	pnew[i][j] = 0.0;
	}
}
x[0] = 0;
y[0] = 0;
for(int i=1; i< nodes; i++){
x[i] = x[i-1] + delta_x ;
y[i] = y[i-1] + delta_y;
}
 



for(int i = 0; i < nodes; i++)
{
for(int j = 0; j < nodes; j++){

analytical[i][j] = (double(-1*0.1*cos(x[i]))/double(sqrt(1-0.5)))*exp(-y[j]*sqrt(1-0.5));
}
}


double B,p; 

B = (pow(delta_x,2))/(0.75*pow(delta_y,2));
p = 1/(2*(1+B));

//std::cout << B << "\n";
// point 1 
for(int z=0; z< 100000; z++)
{
for(int i = 0; i < 1; i++)
{
	for(int j = 0; j < 1; j++){

		pnew[i][j] = p*(2*pold[i+1][j]+2*B*pold[i][j+1] - 2*B*delta_y*0.1*cos(x[0]));
		}
}

//point 2 to N-1
for(int i = 1; i < nodes-1; i++)
{
	for(int j = 0; j < 1; j++){

		pnew[i][j] = p*(pnew[i-1][j] + pold[i+1][j]+2*B*pold[i][j+1] -2*B*delta_y*0.1*cos(x[i]));
		}
}

//point N

pnew[nodes-1][0] = p*(2*pnew[nodes-2][0] + 2*B* pold[nodes-1][1] -2*B*delta_y*0.1*cos(x[nodes-1]));

// x=0 boundary - y 1 to N-1


for(int i = 0; i < 1; i++)
{
	for(int j = 1; j < nodes-1; j++){

		pnew[i][j] = p*(2*pold[i+1][j] + B*pold[i][j+1] + B*pnew[i][j-1]);
		}
}

//left corner x=0 and Y=N
pnew[0][nodes-1] = p*(2*pold[1][nodes-1] + 2*B*pnew[0][nodes-2]);

//inner loops
for(int i = 1; i < nodes-1; i++)
{
	for(int j = 1; j < nodes-1; j++){

		pnew[i][j] = p*(pold[i+1][j] + pnew[i-1][j] + B*pold[i][j+1] + B*pnew[i][j-1]);
		}
}
 //x boundary y to 2-N-1
for(int i = nodes-1; i < nodes; i++)
{
	for(int j = 1; j < nodes-1; j++){

		pnew[i][j] = p*(2*pnew[i-1][j] + B*pold[i][j+1] + B*pnew[i][j-1]);
		}
}
 //y boundary x to 2-N-1
for(int i = 1; i < nodes-1; i++)
{
	for(int j = nodes-1; j < nodes; j++){

		pnew[i][j] = p*(pnew[i-1][j] + pold[i+1][j] + 2*B*pnew[i][j-1]);
		}
}

// right most boundary
pnew[nodes-1][nodes-1] = p*(2*pnew[nodes-2][nodes-1] + 2*B*pnew[nodes-1][nodes-2]);



for(int i = 0; i < nodes; i++)
{
	for(int j = 0; j < nodes; j++){

		psor[i][j] = (1-w)*pold[i][j] + w*pnew[i][j] ;
		}
}


for(int i = 0; i < nodes; i++)
{
	for(int j = 0; j < nodes; j++){

		perr[i][j] = std::abs(psor[i][j] - pold[i][j]) ;
		
		}
}

double sum1=0.0;
double sum2=0.0;
for ( int i = 0; i < nodes; i++ )
{
  for ( int j = 0; j < nodes; j++ )
  {
      sum1+=perr[i][j];
      sum2 += std::abs(pold[i][j]);	
  }
}


err= sum1/sum2;
std::cout << err << "\n";

if(err < 1.e-8){

std::cout << "Solution is converged" << "\n";
break;
}



for ( int i = 0; i < nodes; i++ )
{
  for ( int j = 0; j < nodes; j++ )
  {
      pold[i][j]=psor[i][j];
      	
  }
}


}

// inner u velocites and velocities 
for(int i = 1; i < nodes-1; i++)
{
	for(int j = 0; j < nodes; j++){

		u[i][j] = (psor[i+1][j] - psor[i-1][j])/(2*delta_x) ;
		
		}
}

for(int i = 0; i < nodes; i++)
{
	for(int j = 1; j < nodes-1; j++){

		v[i][j] = (psor[i][j+1] - psor[i][j-1])/(2*delta_y) ;
		
		}
}

// u velocities on boundaries
for(int i = 0; i < 1; i++)
{
	for(int j = 0; j < nodes; j++){

		u[i][j] = (psor[i+1][j] - psor[i][j])/(delta_x) ;
		
		}
}

for(int i = nodes-1; i < nodes; i++)
{
	for(int j = 0; j < nodes; j++){

		u[i][j] = (psor[i][j] - psor[i-1][j])/(delta_x) ;
		
		}
}

//v velocities on boundaries

for(int i = 0; i < nodes; i++)
{
	for(int j = 0; j < 1; j++){

		v[i][j] = (psor[i][j+1] - psor[i][j])/(delta_y) ;
		
		}
}


for(int i = 0; i < nodes; i++)
{
	for(int j = nodes-1; j < nodes; j++){

		v[i][j] = (psor[i][j] - psor[i][j-1])/(delta_y) ;
		
		}
}

std::ofstream write_file("u.dat");
// Write numbers as +x.<13digits>e+00 (width 20)
write_file.setf(std::ios::scientific);
write_file.precision(16);

assert(write_file.is_open());
for (int i=0; i< nodes; i++)
{
for(int j=0; j< nodes; j++){
write_file << u[i][j] << " "; 
}
write_file << "\n";
}
write_file.close();


std::ofstream write_v("v.dat");
// Write numbers as +x.<13digits>e+00 (width 20)
write_v.setf(std::ios::scientific);
write_v.precision(16);

assert(write_v.is_open());
for (int i=0; i< nodes; i++)
{
for(int j=0; j< nodes; j++){
write_v << v[i][j] << " "; 
}
write_v << "\n";
}
write_v.close();

return 0;
}








