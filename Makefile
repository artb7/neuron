CC = g++
CFLAGS = -W -Wall -g -std=c++17
TARGET = test_mat2d 

$(TARGET) : test_mat2d.o Layers.o Mat2d.o
	$(CC) $(CFLAGS) -o $(TARGET) test_mat2d.o Layers.o Mat2d.o

#main.o : main.cpp Layers.hpp Mat2d.hpp 
#$(CC) $(CFLAGS) -c main.cpp

test_mat2d.o : test_mat2d.cpp Layers.hpp Mat2d.hpp 
	$(CC) $(CFLAGS) -c test_mat2d.cpp

Layers.o : Layers.cpp Layers.hpp Mat2d.hpp
	$(CC) $(CFLAGS) -c Layers.cpp

Mat2d.o : Mat2d.cpp Mat2d.hpp
	$(CC) $(CFLAGS) -c Mat2d.cpp

Tensor.o : Tensor.cpp Tensor.hpp
	$(CC) $(CFLAGS) -c Tensor.cpp

clean :
	\rm *.gch *.o main
