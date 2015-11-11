#include<iostream>
#include<cmath>
#include<string>
#include<cassert>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<omp.h>

bool check_prime(int n);
 int main(int argc, char* argv[])
 {
    long int numbers[] = {1500000};
    int k = sizeof(numbers)/sizeof(numbers[0]);
    double time[31]; 
		int i, flag=0 ; 
		int ans=0;
		int first=0, second=0;
	  double ctime1;
    double ctime2;
		for(int z=0; z < k ; z++)
		{
		int count=0;
	for(int t= 2 ; t< 33; t++)
 {
 omp_set_num_threads(t); 
 ctime1 = omp_get_wtime();
#pragma omp parallel for private(i) schedule(static,100)
		for(long int i = 2; i<= numbers[z]/2; i++)
		{
			if(check_prime(i))
		 {
		 		if(check_prime(numbers[z]-i))
		 		{
		 		 ans = i + (numbers[z]-i);
		 		 if(ans == numbers[z])
		 		 {
		 		 count++;
		 		 first = i; 
		 		 second = numbers[z]-i;
		 		 //std::cout << "GoldBach condition holds true" << "\n";
		 		 //std::cout << first << "  "  << second << "\n";
		 		 
		 		 }
		 		}
		 }
		}
		 //std::cout << count << std::endl;
		 ctime2 = omp_get_wtime();
     time[t-2] = (ctime2-ctime1); 
     std::cout << time[t-2] << std::endl;
     }
 }
 
 std::ofstream write_file("speedupdatastatic.dat");
// Write numbers as +x.<13digits>e+00 (width 20)
write_file.setf(std::ios::scientific);
write_file.precision(30);

assert(write_file.is_open());
for (int i=0; i< 31; i++)
{

write_file << time[i] << std::endl;

}
write_file.close();

  return 0;
 }
 
bool check_prime(int n)
 {
 int i;
 bool prime;
 
 prime= true;
 for(int i= 2; i < n/2 ;i++)
 {
 	if(n%i == 0)
 	{
 	prime = false;
 	break;
 	}
 }
 
 return prime;
 }
