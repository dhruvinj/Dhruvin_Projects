#include<iostream>
#include<cmath>
#include<string>
#include<cassert>
#include<fstream>
#include<cstdlib>
#include<time.h>
#include<omp.h>
#include<stdio.h>

long double myFunction(long double x);

 int main(int argc, char* argv[])
 {
 
 /*
 for (int i=0; i<argc; i++)
 {
 std::cout << "Argument " << i << " = " << argv[i];
 std::cout << "\n";
 }
 */
 
 std::string program_name = argv[0];
 unsigned long int number_of_nodes = atoi(argv[1]);
 int t = atof(argv[2]);
 char* file_name = argv[3];

unsigned long int nodes = number_of_nodes;
/*
std::cout << nodes << std::endl;
std::cout << "threads = " << t  << std::endl;
std::cout << file_name << std::endl;
 */
 double time; 
  double ctime1;
  double ctime2;

 long double hx=0.0;
 hx = double(1)/double(nodes-1);

	long double pi= 0;

 unsigned long long int i; double sum =0.0;

 sum =0.0;
omp_set_num_threads(t); 

ctime1 = omp_get_wtime();
#pragma omp parallel for private(i) reduction(+:sum) schedule(guided, 100)
 for( i=1 ; i< nodes -1 ; i++)
 {
 //mid = double(i*hx + (i-1)*hx)/double(2);
 sum = sum + hx*myFunction((i*hx + (i-1)*hx)/double(2));
 }
 
ctime2 = omp_get_wtime();

time = (ctime2-ctime1); 

std::cout << time << std::endl;

  pi = 4.0*sum;

 

std::ofstream write_file(file_name);
// Write numbers as +x.<13digits>e+00 (width 20)
write_file.setf(std::ios::scientific);
write_file.precision(30);

assert(write_file.is_open());

write_file << time << std::endl;

write_file.close();


 
 return 0;
 }
 
 
long double myFunction(long double x)
 {
 return sqrt(1 - x*x);
 }


