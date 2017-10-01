test: test.o Matrix.o
	g++ -Wall -g -o test test.o Matrix.o

test.o: test.cpp Matrix.h
	g++ -Wall -g -c test.cpp  

Matrix.o: Matrix.cpp Matrix.h
	g++ -Wall -g -c Matrix.cpp Matrix.h
