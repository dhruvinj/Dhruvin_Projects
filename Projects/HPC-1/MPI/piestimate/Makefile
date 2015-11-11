all: Run1 2Run
Run1: mpipiestimate.cpp
	mpic++ -o Run1 mpipiestimate.cpp 

2Run: piestimate.cpp
	g++ -o 2Run piestimate.cpp -lrt

clean:
	rm Run1 2Run 

