#include<iostream>
#include<cmath>
#include<string>
#include<cassert>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include "ComplexNumber.hpp"
#include<mpi.h>
#include<sstream>
 int main(int argc, char* argv[])
 {
	 int tag,source,destination,count;
    int buffer;
    MPI_Status status;
	int nodes[] = {800};
  double hx;
 	double hy;

  double* x;
  double* y;
 	double* C;
 x = new double[nodes[0]];
 y = new double[nodes[0]/2];

 double global_total;
 double** Creal;
 double** Cimag;
 int rows = nodes[0]/2, cols = nodes[0];
 Creal = new double*[rows];
 Cimag = new double*[nodes[0]/2];
 
 for(int i = 0; i < rows; i++)
  {
 	Creal[i] = new double[cols];
	Cimag[i] = new double[cols];
  }
  
  hx = double(4)/double(nodes[0]-1);
 hy = double(4)/double(nodes[0]-1);
//double total_sum1 =0.0, total_sum2 =0.0, sum1=0.0, sum2=0.0;
int global_id,color,broad_val, new_id, new_nodes;
int nproc, myrank, ierr;
 MPI_Comm New_Comm;
   
   double time2, time1;
   
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    color = myrank%2;
    global_id = myrank; 
		tag=999;
    MPI_Comm_split(MPI_COMM_WORLD, color,myrank,&New_Comm);
    MPI_Comm_rank(New_Comm,&new_id);
    MPI_Comm_size(New_Comm, &new_nodes);
    	time1 = MPI_Wtime();
    if (color==0)
    {
  double total_sum1 =0.0, total_sum2 =0.0, sum1=0.0, sum2=0.0;

 x[0]=-2;
 y[0] = -2;
 for(int i=1;i< nodes[0];i++)
 	{
 	x[i] = x[i-1] + hx;
 	}
  
  for(int i=1;i< nodes[0]/2;i++)
 	{
 	y[i] = y[i-1] + hy;
 	}
 	
 	for(int i= 0; i< rows ; i++)
  {
  	for(int j=0; j < cols ; j++)
  		{
  		
  		Creal[i][j] = x[j];
  		Cimag[i][j] = y[i];
  		}
  
  }

 
 	int istart, iend ;
 	istart = ((nodes[0]*(nodes[0]/2))/new_nodes)*new_id;
  iend   = ((nodes[0]*(nodes[0]/2))/new_nodes)*(new_id+1);
    

 double real, imag;
 for(int i=istart; i < iend ;i++)
 {
  int a = i/(nodes[0]);
  int b = i%(nodes[0]);
  real = Creal[a][b];
  imag = Cimag[a][b];

	ComplexNumber z1;
 ComplexNumber cstart(real, imag);
 ComplexNumber z0;
 for(int j=0; j< 10000; j++)
 {
 	z1 = z0.CalculatePower(2) + cstart;
 	
 	if(z1.CalculateModulus() > 2)
 	{
 	break;
 	}
 	else if( j == (10000 -1))
 	{
 	sum1 += hx*hx;
 	}
  z0 = z1 ; 
 }
}


ierr=MPI_Reduce(&sum1,&total_sum1,1,MPI_DOUBLE,MPI_SUM,0,New_Comm);


        if(new_id ==0)
   {
       
        std::cout << "individual processor sum1 =" << total_sum1 <<std::endl;
		}
 if(new_id ==0 && myrank ==0)
   {
        
        //std::cout << "individual processor sum1 =" << total_sum2 <<std::endl;
     MPI_Recv(&total_sum2, 1, MPI_DOUBLE,1 , tag, MPI_COMM_WORLD, &status);   
		
		
		global_total = total_sum1 + total_sum2;
		std::cout << global_total << std::endl;
		}


delete[] x;
delete[] y;

  
for (int i=0; i<rows; i++)
 {
 delete[] Creal[i];
  delete[] Cimag[i];
 }
 delete[]  Creal;
 delete[]  Cimag;
  
}


else
{
   double total_sum1 =0.0, total_sum2 =0.0, sum1=0.0, sum2=0.0;
 x[0]=-2;
 y[(nodes[0]/2)-1] = 2 ;
 for(int i=1;i< nodes[0];i++)
 	{
 	x[i] = x[i-1] + hx;
 	}
  
  for(int i=((nodes[0]/2) - 2); i > -1 ;i--)
 	{
 	y[i] = y[i+1] - hy;
 	}
 	
 	for(int i= 0; i< rows ; i++)
  {
  	for(int j=0; j < cols ; j++)
  		{
  		Creal[i][j] = x[j];
  		Cimag[i][j] = y[i];
  		}
  
  }
  
 	int istart, iend ;
 	istart = ((nodes[0]*(nodes[0]/2))/new_nodes)*new_id;
  iend   = ((nodes[0]*(nodes[0]/2))/new_nodes)*(new_id+1);
    

 double real, imag;
 for(int i=istart; i < iend ;i++)
 {
  int a = i/(nodes[0]);
  int b = i%(nodes[0]);
  real = Creal[a][b];
  imag = Cimag[a][b];

 ComplexNumber z1;
 ComplexNumber cstart(real, imag);
 ComplexNumber z0;
 for(int j=0; j< 10000; j++)
 {
 	z1 = z0.CalculatePower(2) + cstart;
 	
 	if(z1.CalculateModulus() > 2)
 	{
 	break;
 	}
 	else if( j == (10000 -1))
 	{
 	sum2 += hx*hx;
 	}
  z0 = z1 ; 
 }

}

 ierr=MPI_Reduce(&sum2,&total_sum2,1,MPI_DOUBLE,MPI_SUM,0,New_Comm);
   
   if(new_id ==0 && myrank ==1)
   {
       
        //std::cout << "individual processor sum1 =" << total_sum2 <<std::endl;
     MPI_Send(&total_sum2, 1, MPI_DOUBLE,0 , tag, MPI_COMM_WORLD);   
		
		}

delete[] x;
delete[] y;

  
for (int i=0; i<rows; i++)
 {
 delete[] Creal[i];
  delete[] Cimag[i];
 }
 delete[]  Creal;
 delete[]  Cimag;
  
}




 time2 = MPI_Wtime() - time1; 
 



    MPI_Finalize();
    
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
      
      
         
      std::ofstream timeval;
	    std::stringstream process1;
			process1 << nproc;
	
	std::string filename1 = "timeval"+process1.str()+".dat";
	
	
	  timeval.open(filename1.c_str() );
	
	  timeval << time2 ;
	
	  timeval.close();
    
      process1.str("");
       
    }


  



 

 /*
 std::cout << elapsed_time[h] << std::endl;
   std::cout << sum << "\n";
  
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
