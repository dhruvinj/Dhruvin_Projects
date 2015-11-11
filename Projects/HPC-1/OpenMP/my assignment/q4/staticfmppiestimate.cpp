#include<iostream>
#include<cmath>
#include<string>
#include<cassert>
#include<fstream>
#include<cstdlib>
#include<time.h>
#include<omp.h>

long double myFunction(long double x);

 int main(int argc, char* argv[])
 {
 long double hx;

 int threads,tid;
//unsigned long long int nodes[] = {1500000000, 2000000000, 5000000000, 1000000000,15000000000};
unsigned long long int nodes[] = { 5e9};
 int k = sizeof(nodes)/sizeof(nodes[0]);
 double elapsed_time[k];
 
 double time[31]; 
  double ctime1;
  double ctime2;
 for(int z=0 ; z < k; z++)
 {
  long double hx=0.0;
 hx = double(1)/double(nodes[z]-1);

	long double pi= 0;

 unsigned long long int i; double sum =0.0;
 for(int t= 2 ; t< 33; t++)
 {
 sum =0.0;
omp_set_num_threads(t); 

ctime1 = omp_get_wtime();
#pragma omp parallel for private(i) reduction(+:sum) schedule(dynamic,1000)
 for( i=1 ; i< nodes[z] -1 ; i++)
 {
 //mid = double(i*hx + (i-1)*hx)/double(2);
 sum = sum + hx*myFunction((i*hx + (i-1)*hx)/double(2));
 }
 
ctime2 = omp_get_wtime();

time[t-2] = (ctime2-ctime1); 

std::cout << time[t-2] << std::endl;

  pi = 4.0*sum;
 std::cout << pi << "\n";

}

 }
 
std::ofstream write_file("speedupdatadynamic.dat");
// Write numbers as +x.<13digits>e+00 (width 20)
write_file.setf(std::ios::scientific);
write_file.precision(30);

assert(write_file.is_open());
for (int i=0; i< 31; i++)
{

write_file << time[i] << std::endl;

}
write_file.close();
/*
  std::ofstream write_v("processors.dat");
	// Write numbers as +x.<13digits>e+00 (width 20)
	write_v.setf(std::ios::scientific);
	write_v.precision(30);

	assert(write_v.is_open());
	for (int i=2; i< 33; i++)
	{

	write_v << nodes[i] <<  "\n"; 

	}
	write_v.close();

*/

 
 return 0;
 }
 
 
long double myFunction(long double x)
 {
 return sqrt(1 - x*x);
 }


