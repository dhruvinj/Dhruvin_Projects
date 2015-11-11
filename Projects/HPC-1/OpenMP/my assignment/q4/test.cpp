
#include<iostream>
#include<cmath>
#include<string>
#include<cassert>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include <omp.h> 
int main()
{
#pragma omp parallel
{
int ID = omp_get_thread_num();
std::cout <<  "hello" << ID  << std::endl;
std::cout << "world" << ID  << std::endl;
}

return 0;
}

