#include<iostream>
#include<cmath>
#include<string>
#include<cassert>
#include<fstream>
#include<cstdlib>

void tdma(int ibeg , int iend, double* aa, double* bb, double* cc, double* dd);
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
double p_ans_old[nodes][nodes];
double p_ans_x[nodes][nodes];
double p_ans_y[nodes][nodes];
double perr[nodes][nodes];
double psor[nodes][nodes];
double u[nodes][nodes];
double v[nodes][nodes];
double err;

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
for(int i = 0; i < nodes; i++)
{
for(int j = 0; j < nodes; j++){

p_ans_old[i][j] = 0.0;
p_ans_x[i][j] = 0.0;
}
}


double B,p; 

B = (pow(delta_x,2))/(0.75*pow(delta_y,2));
p = 1/(2*(1+B));
double* aa = new double[nodes];
double* bb = new double[nodes];
double* cc = new double[nodes];
double* dd = new double[nodes];

// point 1 
for(int z=0; z< 100000; z++)
{

	//x sweep
	//first row
	for(int j = 0; j<1; j++)
	{
	aa[0] = 0;
	bb[0] =-2*(1+B);
	cc[0] = 2;
	dd[0] = -B*(2*p_ans_old[0][j+1] - 2*delta_y*0.1*cos(x[0]));
	for(int i = 1; i < nodes-1; i++)
	{
		aa[i] = 1;
		bb[i] =-2*(1+B);
		cc[i] = 1;
		dd[i] = -B*(2*p_ans_old[i][j+1] - 2*delta_y*0.1*cos(x[i]));
	}
	aa[nodes-1] = 2;
	bb[nodes-1] =-2*(1+B);
	cc[nodes-1] = 0;
	dd[nodes-1] = -B*(2*p_ans_old[nodes-1][j+1] - 2*delta_y*0.1*cos(x[nodes-1]));

	tdma(0,nodes-1, aa, bb, cc, dd);

	for(int i=0;i< nodes;i++)
	{
	p_ans_x[i][j] = dd[i];
	}
	}

	// rows 2 to nodes-1
	for(int j = 1; j<nodes-1; j++)
	{
	aa[0] = 0;
	bb[0] =-2*(1+B);
	cc[0] = 2;
	dd[0] = -B*(p_ans_old[0][j+1] + p_ans_x[0][j-1]);
	for(int i = 1; i < nodes-1; i++)
	{
		aa[i] = 1;
		bb[i] =-2*(1+B);
		cc[i] = 1;
		dd[i] = -B*(p_ans_old[i][j+1] + p_ans_x[i][j-1]);
	}
	aa[nodes-1] = 2;
	bb[nodes-1] =-2*(1+B);
	cc[nodes-1] = 0;
	dd[nodes-1] = -B*(p_ans_old[nodes-1][j+1] + p_ans_x[nodes-1][j-1]);

	tdma(0,nodes-1, aa, bb, cc, dd);

	for(int i=0;i< nodes;i++)
	{
	p_ans_x[i][j] = dd[i];
	}
	}
	// last row
	for(int j = nodes-1; j<nodes; j++)
	{
	aa[0] = 0;
	bb[0] =-2*(1+B);
	cc[0] = 2;
	dd[0] = -B*(2*p_ans_x[0][j-1]);
	for(int i = 1; i < nodes-1; i++)
	{
		aa[i] = 1;
		bb[i] =-2*(1+B);
		cc[i] = 1;
		dd[i] = -B*(2*p_ans_x[i][j-1]);
	}
	aa[nodes-1] = 2;
	bb[nodes-1] =-2*(1+B);
	cc[nodes-1] = 0;
	dd[nodes-1] = -B*(2*p_ans_x[nodes-1][j-1]);

	tdma(0,nodes-1, aa, bb, cc, dd);

	for(int i=0;i< nodes;i++)
	{
	p_ans_x[i][j] = dd[i];
	}
	}


	//y sweep

	//first column
	for(int i = 0; i<1; i++)
	{
	aa[0] = 0;
	bb[0] =-2*(1+B);
	cc[0] = 2*B;
	dd[0] = -2*p_ans_x[i+1][0] + 2*B*delta_y*0.1*cos(x[0]);
	for(int j = 1; j < nodes-1; j++)
	{
		aa[j] = B;
		bb[j] =-2*(1+B);
		cc[j] = B;
		dd[j] = -(2*p_ans_x[i+1][j]);
	}
	aa[nodes-1] = 2*B;
	bb[nodes-1] =-2*(1+B);
	cc[nodes-1] = 0;
	dd[nodes-1] = -(2*p_ans_x[i+1][nodes-1]);

	tdma(0,nodes-1, aa, bb, cc, dd);

	for(int j=0;j< nodes;j++)
	{
	p_ans_y[i][j] = dd[j];
	}
	}

	//from column 2 to N-1

	for(int i = 1; i<nodes-1; i++)
	{
	aa[0] = 0;
	bb[0] =-2*(1+B);
	cc[0] = 2*B;
	dd[0] = -(p_ans_x[i+1][0]+ p_ans_y[i-1][0]) + 2*B*delta_y*0.1*cos(x[i]);
	for(int j = 1; j < nodes-1; j++)
	{
		aa[j] = B;
		bb[j] =-2*(1+B);
		cc[j] = B;
		dd[j] = -(p_ans_x[i+1][j] + p_ans_y[i-1][j]);
	}
	aa[nodes-1] = 2*B;
	bb[nodes-1] =-2*(1+B);
	cc[nodes-1] = 0;
	dd[nodes-1] = -(p_ans_x[i+1][nodes-1]+p_ans_y[i-1][nodes-1]);

	tdma(0,nodes-1, aa, bb, cc, dd);

	for(int j=0;j< nodes;j++)
	{
	p_ans_y[i][j] = dd[j];
	}
	}


	//from column N

	for(int i = nodes-1; i<nodes; i++)
	{
	aa[0] = 0;
	bb[0] =-2*(1+B);
	cc[0] = 2*B;
	dd[0] = -(2*p_ans_y[i-1][0]) + 2*B*delta_y*0.1*cos(x[i]);
	for(int j = 1; j < nodes-1; j++)
	{
		aa[j] = B;
		bb[j] =-2*(1+B);
		cc[j] = B;
		dd[j] = -(2*p_ans_y[i-1][j]);
	}
	aa[nodes-1] = 2*B;
	bb[nodes-1] =-2*(1+B);
	cc[nodes-1] = 0;
	dd[nodes-1] = -(2*p_ans_y[i-1][nodes-1]);

	tdma(0,nodes-1, aa, bb, cc, dd);

	for(int j=0;j< nodes;j++)
	{
	p_ans_y[i][j] = dd[j];
	}
	}



	for(int i = 0; i < nodes; i++)
	{
		for(int j = 0; j < nodes; j++){

			perr[i][j] = std::abs(p_ans_y[i][j] - p_ans_old[i][j]) ;
		
			}
	}

	double sum1=0.0;
	double sum2=0.0;
	for ( int i = 0; i < nodes; i++ )
	{
	  for ( int j = 0; j < nodes; j++ )
	  {
		  sum1+=perr[i][j];
		  sum2 += std::abs(p_ans_old[i][j]);	
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
		  p_ans_old[i][j]=p_ans_y[i][j];
		  	
	  }
	}


}

for ( int i = 0; i < nodes; i++ )
	{
	  for ( int j = 0; j < nodes; j++ )
	  {
		  psor[i][j]=p_ans_y[i][j];
		  	
	  }
	}

// inner u velocites and v velocities 
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

delete[] aa;
delete[] bb;
delete[] cc;
delete[] dd;

std::ofstream write_file("adiu.dat");
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


std::ofstream write_v("adiv.dat");
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



void tdma(int ibeg , int iend, double* aa, double* bb, double* cc, double* dd)
{
double r;
for (int i = ibeg+1; i< iend +1; i++)
{

r = aa[i]/bb[i-1];
bb[i] = bb[i] - r*cc[i-1];
dd[i] = dd[i]-r*dd[i-1];
}

dd[iend] = dd[iend]/bb[iend];

//back substitution

for(int i = iend -1; i > ibeg-1; i--)
{

dd[i] = (dd[i]-cc[i]*dd[i+1])/bb[i];

}


}




