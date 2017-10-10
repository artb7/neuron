CC = g++
CFLAGS = -W -Wall -g -std=c++11
TARGET = main

$(TARGET) : main.o Layers.o Tensor.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o Layers.o Tensor.o

main.o : main.cpp Layers.h Tensor.h 
	$(CC) $(CFLAGS) -c main.cpp

Layers.o : Layers.cpp Layers.h Tensor.h
	$(CC) $(CFLAGS) -c Layers.cpp

Tensor.o : Tensor.cpp Tensor.h
	$(CC) $(CFLAGS) -c Tensor.cpp

clean :
	\rm *.o main
