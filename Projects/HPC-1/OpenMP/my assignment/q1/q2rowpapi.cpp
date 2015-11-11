    #include<iostream>
    #include<cmath>
    #include<string>
    #include<cassert>
    #include<fstream>
    #include<cstdlib>
    #include<ctime>
		#include<papi.h>
		#include<stdio.h>
		
    int main(int argc, char* argv[])
    {
    
     int nodes[] = { 20000};
     int k = sizeof(nodes)/sizeof(nodes[0]);
     double msecs[k];
	
    clock_t start, end;
    //std::cout << nodes <<"\n";
    int a=0;
    for(int z=0; z < k; z++)
    {
    
    	long long counters[2];
	  int PAPI_events[] = {PAPI_L1_TCM,	PAPI_L2_TCM };

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
     
		float real_time, proc_time,mflops;
    long long flpops;
    float ireal_time, iproc_time, imflops;
     long long iflpops;
     int retval;
   
		if((retval=PAPI_flops(&ireal_time,&iproc_time,&iflpops,&imflops)) < PAPI_OK)
 {
 printf("Could not initialise PAPI_flops \n");
 printf("Your platform may not support floating point operation event.\n");
 printf("retval: %d\n", retval);
 return(1);
 }
  
    for(int i = 0; i< nodes[z]; i++)
    {
        for(int j=0;j<nodes[z];j++)
        {
        C[i][j] = A[i][j] + B[i][j];
        
        }
    }
    
    if((retval=PAPI_flops( &real_time, &proc_time, &flpops, &mflops))<PAPI_OK)
 {
 printf("retval: %d\n", retval);
 return(1);
 }

printf("Real_time: %f Proc_time: %f Total flpops: %lld MFLOPS: %f\n",
 real_time, proc_time,flpops,mflops);
 
    
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
