    #include<iostream>
    #include<cmath>
    #include<string>
    #include<cassert>
    #include<fstream>
    #include<cstdlib>
    #include<ctime>
		#include<papi.h>
		
    int main(int argc, char* argv[])
    {

    int nodes[] = {100, 1000, 10000, 15000 , 20000};
     int k = sizeof(nodes)/sizeof(nodes[0]);
     
		
  
   
    double msecs[k];
	
    clock_t start, end;
    //std::cout << nodes <<"\n";
    int a=0;
    for(int z=0; z < k; z++)
    {
    
    	long long counters[1];
	  int PAPI_events[] = {PAPI_FP_OPS};

    double** A;
    double** B;
    double** C;

    A = new double* [nodes[z]];
    B = new double* [nodes[z]];
    C = new double* [nodes[z]];

    for (int i=0; i<nodes[z]; i++)
    {
    A[i] = new double [nodes[z]];
    B[i] = new double [nodes[z]];
    C[i] = new double [nodes[z]];

    }
	
    for(int i = 0; i< nodes[z]; i++)
    {
        for(int j=0;j<nodes[z];j++)
        {
        A[i][j] = 1;
        B[i][j] = 2;
        }
    }
    PAPI_library_init(PAPI_VER_CURRENT);
    int w;
    w = PAPI_start_counters( PAPI_events, 1 );
  
    for(int j = 0; j< nodes[z]; j++)
    {
        for(int i=0;i<nodes[z];i++)
        {
        C[i][j] = A[i][j] + B[i][j];
        
        }
    }
    PAPI_read_counters( counters, 1 );
		std::cout << counters[0]  << std::endl;
    for (int i=0; i<nodes[z]; i++)
    {
    delete[] A[i] ;
    delete[] B[i] ;
    delete[] C[i] ;
    }

    delete[] A ;
    delete[] B ;
    delete[] C ;


    }



    return 0;
    }
