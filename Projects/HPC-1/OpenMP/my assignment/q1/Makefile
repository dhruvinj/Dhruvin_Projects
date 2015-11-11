all: 1Run 2Run 3Run 4Run
1Run: q2row.cpp
	g++ -pg -o 1Run q2row.cpp

2Run: q2col.cpp
	g++ -pg -o 2Run q2col.cpp

3Run: q2rowpapi.cpp
	g++ -o  3Run q2rowpapi.cpp -I/zoidberg1/data/users/dhruvinj/Software/Papi/install/include -L/zoidberg1/data/users/dhruvinj/Software/Papi/install/lib  -lpapi
	
4Run: q2colpapi.cpp
	g++ -o 4Run q2colpapi.cpp -I/zoidberg1/data/users/dhruvinj/Software/Papi/install/include -L/zoidberg1/data/users/dhruvinj/Software/Papi/install/lib  -lpapi
