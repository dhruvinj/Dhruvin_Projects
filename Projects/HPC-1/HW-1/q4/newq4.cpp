    #include<iostream>
    #include<cmath>
    #include<string>
    #include<cassert>
    #include<fstream>
    #include<cstdlib>
    #include<ctime>
    #include<mkl.h>
    
     int main(int argc, char* argv[])
    {
     int nodes[] = {500, 600,750,1000};
     int k = sizeof(nodes)/sizeof(nodes[0]);

     double msecs[k];
     clock_t start, end;
     
    for(int z=0; z < k; z++)
    {

    double** A = new double* [nodes[z]];
    double** B = new double* [nodes[z]];
    double** C = new double* [nodes[z]];
	int m,n,r, alpha,beta;
	m = nodes[z];
	n = nodes[z];
	r = nodes[z];
	alpha=1;
	beta=0;
	
     for (int i=0; i<nodes[z]; i++)
    {
    A[i] = new double [nodes[z]];
    B[i] = new double [nodes[z]];
    C[i] = new double [nodes[z]];
    }
    
    double* E = new double [nodes[z]*nodes[z]];
	double* F = new double [nodes[z]*nodes[z]];
	double* G = new double [nodes[z]*nodes[z]];
	
	 for(int i = 0; i< nodes[z]; i++)
    {
        for(int j=0;j<nodes[z];j++)
        {
        A[i][j] = 2.0;
        B[i][j] = 3.0;
        }
    }
    
      for(int i = 0; i< nodes[z]; i++)
    {
        for(int j=0;j<nodes[z];j++)
        {
        E[i*nodes[z]+j] = A[i][j];
        F[i*nodes[z]+j] = B[i][j];
        }
    }
    
    start = clock();


    cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, m, n, r, alpha, E, r, F, n, beta, G, n);

    end = clock();
    
     for(int i = 0; i< nodes[z]; i++)
    {
        for(int j=0;j<nodes[z];j++)
        {
        C[i][j] = G[i*nodes[z]+j];
        
        }
    }
    
   
    /*
     for(int i = 0; i< nodes[z]; i++)
    {
        for(int j=0;j<nodes[z];j++)
        {
        std::cout << C[i][j]<< " ";
        
        }
    std::cout << "\n";
    }
    */
      msecs[z] =  ((double) (end - start)) * 1000 / CLOCKS_PER_SEC ;
      std::cout << msecs[z] <<"\n";
  

    
    delete[] A ;
    delete[] B ;
    delete[] C ;
    
    delete[] E ;
    delete[] F ;
    delete[] G ;



    }

std::ofstream write_file("mkl.dat");
// Write numbers as +x.<13digits>e+00 (width 20)
write_file.setf(std::ios::scientific);
write_file.precision(30);

assert(write_file.is_open());
for (int i=0; i< 4; i++)
{

write_file << msecs[i] << "\n";

}
write_file.close();

    
    return 0;
    }
    
