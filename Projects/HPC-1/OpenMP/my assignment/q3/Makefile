all: Run1 2Run 3Run 4Run 5Run
Run1: goldbach.cpp
	g++ -o Run1 goldbach.cpp -lrt -I/zoidberg1/data/users/dhruvinj/Software/Papi/install/include -L/zoidberg1/data/users/dhruvinj/Software/Papi/install/lib  -lpapi

2Run: staticgoldbach.cpp
	g++ -fopenmp staticgoldbach.cpp -o 2Run
	
3Run: dynamicgoldbach.cpp
	g++ -fopenmp dynamicgoldbach.cpp -o 3Run
	
4Run: guidedgoldbach.cpp
	g++ -fopenmp guidedgoldbach.cpp -o 4Run

5Run: speedgoldbach.cpp
	g++ -fopenmp speedgoldbach.cpp -o 5Run

