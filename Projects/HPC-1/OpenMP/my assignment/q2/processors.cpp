    #include<iostream>
    #include<cmath>
    #include<string>
    #include<cassert>
    #include<fstream>
    #include<cstdlib>
    #include<ctime>
		
    int main(int argc, char* argv[])
    {
		int processors[30];
    for(int i = 0; i< 31; i++)
    {
      processors[i] = i+2;
      	std::cout << processors[i]  << std::endl;
    }
		
   

 std::ofstream write_file("processors.dat");
// Write numbers as +x.<13digits>e+00 (width 20)
write_file.setf(std::ios::scientific);
write_file.precision(30);

assert(write_file.is_open());
for (int i=0; i< 31; i++)
{

write_file << processors[i] << std::endl;

}
write_file.close();
    



    return 0;
    }
