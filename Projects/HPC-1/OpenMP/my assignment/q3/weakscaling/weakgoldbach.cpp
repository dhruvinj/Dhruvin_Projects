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
 		 long double hx;
 		int even = 6;
 		std::string program_name = argv[0];
 		unsigned long int number_of_nodes = atoi(argv[1]);
	 int t = atof(argv[2]);
 	 char* file_name = argv[3];
 		int numbers[number_of_nodes];
    
    
    for (int i=0;i < number_of_nodes;i++)
	  {       
	  even+=2;
		numbers[i] = even ; 
		//std::cout << numbers[i] << std::endl;
		}
  
    double time; 
		int i, flag=0 ; 
		int ans=0;
		int first=0, second=0;
	  double ctime1;
    double ctime2;
		
		int count=0;
		int z;
		 omp_set_num_threads(t); 
 		 ctime1 = omp_get_wtime();
		#pragma omp parallel for schedule(static,10)
		for(int z=0; z < number_of_nodes ; z++)
		{
		
		for(long int i = 2; i < numbers[z]/2; i++)
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
		 		 //std::cout << first << "  "  << second << "\n";
		 		 
		 		 }
		 		}
		 }
		}
		}
		//std::cout << count << std::endl;
		 ctime2 = omp_get_wtime();
     time = (ctime2-ctime1); 
     std::cout << time << std::endl;
     
 
 
 std::ofstream write_file(file_name);
// Write numbers as +x.<13digits>e+00 (width 20)
write_file.setf(std::ios::scientific);
write_file.precision(30);

assert(write_file.is_open());


write_file << time << std::endl;

write_file.close();

  return 0;
 }
 
bool check_prime(int n)
 {
 int i;
 bool prime;
 
 prime= true;
 for(int i= 2; i < sqrt(n) ;i++)
 {
 	if(n%i == 0)
 	{
 	prime = false;
 	break;
 	}
 }
 
 return prime;
 }
