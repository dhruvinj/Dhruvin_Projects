all: Run1 Run2 Run3 Run4
Run1: q3.cpp
	g++ -o Run1 q3.cpp

Run2: q3.cpp
	g++ -O3 -o Run2 q3.cpp
Run3: mklq3.cpp
	icpc mklq3.cpp -o Run3 -mkl
Run4: blasq3.cpp
	g++ blasq3.cpp -o Run4  -I${OPENBLAS_DIR}/include  -L${OPENBLAS_DIR}/lib  -lopenblas 
clean:
	rm Run1 Run2 Run3 Run4
