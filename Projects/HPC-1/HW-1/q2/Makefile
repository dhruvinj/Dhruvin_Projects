all: Run1 Run2 Run3 Run4 Run5 Run6 Run7 Run8
Run1: q2row.cpp
	g++ -o Run1 q2row.cpp

Run2: q2row.cpp
	g++ -O3 -o Run2 q2row.cpp

Run3: q2col.cpp
	g++ -o Run3 q2col.cpp

Run4: q2col.cpp
	g++ -O3 -o Run4 q2col.cpp

Run5: q2row.cpp
	icpc q2row.cpp -o Run5

Run6: q2row.cpp
	icpc q2row.cpp -O2 -o run6

Run7: q2col.cpp
	icpc q2col.cpp -o run7

Run8: q2col.cpp
	icpc q2col.cpp -O2 -o run8
clean:
	rm  Run1 Run2 Run3 Run4 Run5 Run6 Run7 Run8
