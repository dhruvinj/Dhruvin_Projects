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
unsigned long long int nodes[] = {1e9, 3e9, 5e9, 7e9};
 int k = sizeof(nodes)/sizeof(nodes[0]);
 
 double time[k]; 
  double ctime1;
  double ctime2;
 for(int z=0 ; z < k; z++)
 {
  long double hx=0.0;
 hx = double(1)/double(nodes[z]-1);

	long double pi= 0;

 unsigned long long int i; double sum =0.0;
omp_set_num_threads(24); 

ctime1 = omp_get_wtime();
#pragma omp parallel for private(i) reduction(+:sum)  schedule(dynamic,1000)
 for( i=1 ; i< nodes[z] -1 ; i++)
 {
 //mid = double(i*hx + (i-1)*hx)/double(2);
 sum = sum + hx*myFunction((i*hx + (i-1)*hx)/double(2));
 }
 
ctime2 = omp_get_wtime();

time[z] = (ctime2-ctime1); 

std::cout << time[z] << std::endl;

  pi = 4.0*sum;
 std::cout << pi << "\n";


 }
std::ofstream write_file("dynamicdata.dat");
// Write numbers as +x.<13digits>e+00 (width 20)
write_file.setf(std::ios::scientific);
write_file.precision(30);

assert(write_file.is_open());
for (int i=0; i< k; i++)
{

write_file << time[i] << std::endl;

}
write_file.close();

std::ofstream write_v("nodes.dat");
// Write numbers as +x.<13digits>e+00 (width 20)
write_v.setf(std::ios::scientific);
write_v.precision(30);

assert(write_v.is_open());
for (int i=0; i< k; i++)
{

write_v << nodes[i] <<  "\n"; 

}
write_v.close();

 
 
 return 0;
 }
 
 
long double myFunction(long double x)
 {
 return sqrt(1 - x*x);
 }


