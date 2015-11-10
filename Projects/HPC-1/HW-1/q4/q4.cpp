    #include<iostream>
    #include<cmath>
    #include<string>
    #include<cassert>
    #include<fstream>
    #include<cstdlib>
    #include<ctime>

    int main(int argc, char* argv[])
    {

    int nodes[] = {100, 500,750,1000};
     int k = sizeof(nodes)/sizeof(nodes[0]);

    double msecs[k];

    clock_t start, end;
    //std::cout << nodes <<"\n";
    int a=0;
    for(int z=0; z < k; z++)
    {

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
        A[i][j] = 2;
        B[i][j] = 3;
        }
    }
    

    start = clock();
      for(int i=0;i<nodes[z];i++)
        {
            for(int j=0;j<nodes[z];j++)
            {
                C[i][j]=0;
                for(int k=0;k<nodes[z];k++)
                {
                    C[i][j]=C[i][j]+A[i][k]*B[k][j];
                }
            }
         }
    end = clock();
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
    msecs[a] =  ((double) (end - start)) * 1000 / CLOCKS_PER_SEC ;
    std::cout << msecs[a] <<"\n";
    a=a+1;


    delete[] A ;
    delete[] B ;
    delete[] C ;
    	   
    }

std::ofstream write_file("go.dat");
// Write numbers as +x.<13digits>e+00 (width 20)
write_file.setf(std::ios::scientific);
write_file.precision(30);

assert(write_file.is_open());
for (int i=0; i< 4; i++)
{

write_file << msecs[i] << "\n";

}
write_file.close();

std::ofstream write_v("nodes.dat");
// Write numbers as +x.<13digits>e+00 (width 20)
write_v.setf(std::ios::scientific);
write_v.precision(30);

assert(write_v.is_open());
for (int i=0; i< 4


; i++)
{

write_v << nodes[i] <<  "\n"; 

}
write_v.close();


    return 0;
    }
