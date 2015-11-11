#include<iostream>
#include<cmath>
#include<string>
#include<cassert>
#include<fstream>
#include<cstdlib>
#include<time.h>

long double myFunction(long double x);

 int main(int argc, char* argv[])
 {
 long double hx;

//unsigned long long int nodes[] = {1500000000, 2000000000, 5000000000, 1000000000,15000000000};
unsigned long int nodes[] = {1e9, 2e9,5e9};
 int k = sizeof(nodes)/sizeof(nodes[0]);
 double elapsed_time[k];
  timespec start, end;
 double time= 0; 
  double ctime1;
  double ctime2;
 for(int z=0 ; z < k; z++)
 {
  long double hx=0.0;
 hx = double(1)/double(nodes[z]-1);

	long double pi= 0;

 unsigned long long int i; double sum =0.0;


 
	clock_gettime(CLOCK_REALTIME,&start);

   
 for( i=1 ; i< nodes[z] -1 ; i++)
 {
 //mid = double(i*hx + (i-1)*hx)/double(2);
 sum = sum + hx*myFunction((i*hx + (i-1)*hx)/double(2));
 }
   
    clock_gettime(CLOCK_REALTIME,&end);
		
     elapsed_time[z] = 1e9 * (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec);
 
     std::cout << elapsed_time[z] << std::endl;

  pi = 4.0*sum;
 std::cout << pi << "\n";


 }
 /*
 std::ofstream write_file("nonparallel.dat");
// Write numbers as +x.<13digits>e+00 (width 20)
write_file.setf(std::ios::scientific);
write_file.precision(30);

assert(write_file.is_open());
for (int i=0; i< k; i++)
{

write_file << elapsed_time[i] << "\n";

}
write_file.close();
 */
 return 0;
 }
 
 
long double myFunction(long double x)
 {
 return sqrt(1 - x*x);
 }


