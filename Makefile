main : main.o Tensor.o
	g++ -Wall -g main.o Tensor.o -o main

main.o : main.cpp Tensor.h
	g++ -Wall -g -c main.cpp

Tensor.o : Tensor.cpp Tensor.h
	g++ -Wall -g -c Tensor.cpp

clean :
	\rm *.o main
