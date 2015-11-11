all: Run1 2Run 3Run 4Run
Run1: piestimate.cpp
	g++ -o Run1 piestimate.cpp -lrt 

2Run: staticfmppiestimate.cpp
	 g++ -fopenmp -o 2Run staticfmppiestimate.cpp 

3Run: dynamicfmppiestimate.cpp
	g++ -fopenmp -o 3Run dynamicfmppiestimate.cpp 

4Run: guidedfmppiestimate.cpp
	g++ -fopenmp -o 4Run guidedfmppiestimate.cpp 
	
clean:
	rm Run1 2Run 3Run 4Run

