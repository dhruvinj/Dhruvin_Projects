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
    //int numbers[] = {100, 1000, 10000, 15000 , 20000};
    int numbers[] = {50};
    int k = sizeof(numbers)/sizeof(numbers[0]);
    double time[k]; 
		int i, flag=0 ; 
		int ans=0;
		int first=0, second=0;
	  double ctime1;
    double ctime2;
		for(int z=0; z < k ; z++)
		{
		int count=0;
	omp_set_num_threads(24); 
	ctime1 = omp_get_wtime();
#pragma omp parallel for reduction(+:count) private(i) schedule(static, 100)
		for(int i = 2; i<= numbers[z]/2; i++)
		{
			if(check_prime(i))
		 {
		 		if(check_prime(numbers[z]-i))
		 		{
		 		 ans = i + (numbers[z]-i);
		 		 if(ans == numbers[z])
		 		 {
		 		 count += 1;
		 		 first = i; 
		 		 second = numbers[z]-i;
		 		 //std::cout << "GoldBach condition holds true" << "\n";
		 		// std::cout << first << "  "  << second << "\n";
		 		 
		 		 }
		 		}
		 }
		}
		 std::cout << count << std::endl;
		 ctime2 = omp_get_wtime();
     time[z] = (ctime2-ctime1); 
     std::cout << time[z] << std::endl;
 }

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
