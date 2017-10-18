CC = g++
CFLAGS = -W -Wall -g -std=c++17
TARGET = main

$(TARGET) : main.o Layers.o Tensor.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o Layers.o Tensor.o

main.o : main.cpp Layers.hpp Tensor.hpp 
	$(CC) $(CFLAGS) -c main.cpp

Layers.o : Layers.cpp Layers.hpp Tensor.hpp
	$(CC) $(CFLAGS) -c Layers.cpp

Tensor.o : Tensor.cpp Tensor.hpp
	$(CC) $(CFLAGS) -c Tensor.cpp

clean :
	\rm *.gch *.o main
