#include<iostream>
#include<cmath>
#include<string>
#include<cassert>
#include<fstream>
#include<cstdlib>
#include<time.h>
#include<mpi.h>
#include<sstream>

 int main(int argc, char* argv[])
 {
 
 
  unsigned long int number_of_nodes = atoi(argv[1]);


//unsigned long int nodes = number_of_nodes;

 unsigned long int nodes[] = {number_of_nodes};
 int k = sizeof(nodes)/sizeof(nodes[0]);
 
 unsigned long int istart, iend, r;
 
 int nproc, myrank, ierr;
 
   double  hx, x,f,sum, total_sum, pi;
   double time2, time1;
   
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
 
 		if(myrank == 0) {
       std::cout << "MPI version with tasks =" <<  nproc << std::endl;
       std::cout << "Number of intervals:" <<  nodes[0] << std::endl;
       
       std::string file = "nproc"; 
       
      std::ofstream piestimate;
	    std::stringstream process;
			process << nproc;
	
	std::string filename = "piestimate"+process.str()+".dat";
	
	
	  piestimate.open(filename.c_str() );
	
	  piestimate << nproc ;
	
	  piestimate.close();
    
      process.str("");
       
    }
    if (r = nodes[0] % nproc) {
       if(myrank == 0) {
         std::cout << "The number of process must divide exactly " << nodes[0] << std::endl;
          MPI_Finalize();
          return 1;
       }  
    }
 		time1 = MPI_Wtime();
 		istart = (nodes[0]/nproc)*myrank + 1;
    iend   = (nodes[0]/nproc)*(myrank+1);
    sum = 0.0;
    total_sum = 0.0;
 		
 		hx = double(1)/double(nodes[0]-1);
 
 		for (unsigned long int i = istart ; i <= iend; i++) {
        x = ((i*hx + (i-1)*hx)/double(2));
        f = 4.0 / (1.0 + x*x);
        sum = sum + hx*f;
        //sum = sum + hx*myFunction((i*hx + (i-1)*hx)/double(2));
    }
 		
 		 ierr=MPI_Reduce(&sum,&total_sum,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
 		 time2 = MPI_Wtime() - time1; 
 		 
 		 pi = total_sum;
 		 
 		 
 		 if(myrank == 0) {
       std::cout << "Computed PI  " << pi << std::endl;
      
       std::cout << "Elapsed time (s) = " << time2 << std::endl ;
       
      std::string file1 = "time2"; 
       
      std::ofstream timeval;
	    std::stringstream process;
			process << nproc;
	
	std::string filename1 = "timeval"+process.str()+".dat";
	
	
	  timeval.open(filename1.c_str() );
	
	  timeval << time2 ;
	
	  timeval.close();
    
      process.str("");
    }

    MPI_Finalize();
    
      //std::cout << "Computed PI  " << pi << std::endl;
 		 
 return 0;
 }
