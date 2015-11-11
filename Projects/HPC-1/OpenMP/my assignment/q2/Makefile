all: Run1 2Run 3Run 4Run 5Run 6Run 7Run 
Run1: mandelbrot.cpp
	g++ -o Run1 mandelbrot.cpp -lrt 

2Run: staticompmandelbrot.cpp
	 g++ -fopenmp -o 2Run staticompmandelbrot.cpp 

3Run: dynamicompmandelbrot.cpp
	g++ -fopenmp -o 3Run dynamicompmandelbrot.cpp 

4Run: guidedompmandelbrot.cpp
	g++ -fopenmp -o 4Run guidedompmandelbrot.cpp 

5Run: speedupmandelbrot.cpp
	g++ -fopenmp -o 5Run speedupmandelbrot.cpp 
	
6Run: dynamicmandelbrot.cpp
	g++ -fopenmp -o 6Run dynamicmandelbrot.cpp 
	
7Run: guidedmandelbrot.cpp
	g++ -fopenmp -o 7Run guidedmandelbrot.cpp 
