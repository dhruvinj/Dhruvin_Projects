#include<iostream>
#include<cmath>
#include<string>
#include<cassert>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<papi.h>

bool check_prime(int n);
 int main(int argc, char* argv[])
 {
    int numbers[] = {100,  10000, 150000 , 2000000};
   //long int numbers[] = {1500000};
    int k = sizeof(numbers)/sizeof(numbers[0]);
    double elapsed_time[k];
		int i, flag=0 ; 
		int ans=0;
		int first=0, second=0;
		timespec start, end;
		for(int z=0; z < k ; z++)
		{
		 long long counters[2];
	 int PAPI_events[] = {PAPI_L1_TCM,	PAPI_L2_TCM };
		int count=0;
	clock_gettime(CLOCK_REALTIME,&start);
	PAPI_library_init(PAPI_VER_CURRENT);
    int w;
    w = PAPI_start_counters( PAPI_events, 2 );
		for(long int i = 2; i<= numbers[z]/2; i++)
		{
			if(check_prime(i))
		 {
		 		if(check_prime(numbers[z]-i))
		 		{
		 		 ans = i + (numbers[z]-i);
		 		 if(ans == numbers[z])
		 		 {
		 		 count = count + 1;
		 		 first = i; 
		 		 second = numbers[z]-i;
		 		// std::cout << "GoldBach condition holds true" << "\n";
		 		// std::cout << first << "\n";
		 		// std::cout << second << "\n";
		 		 //break;
		 		 }
		 		}
		 }
		}
		  PAPI_read_counters( counters, 2 );
		std::cout << counters[0] << " " << counters[1] << std::endl;
 
		 clock_gettime(CLOCK_REALTIME,&end);
		// std::cout << count << std::endl;
     elapsed_time[z] = 1e9 * (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec);
 
     //std::cout << elapsed_time[z] << std::endl;
 }
 /*
  std::ofstream write_file("nonparallel.dat");
// Write numbers as +x.<13digits>e+00 (width 20)
write_file.setf(std::ios::scientific);
write_file.precision(30);

assert(write_file.is_open());
for (int i=0; i< 1; i++)
{

write_file << elapsed_time[i] << "\n";

}
write_file.close();
*/
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
