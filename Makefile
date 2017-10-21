CC = g++
CFLAGS = -W -Wall -g -std=c++17
TARGET = test_layers

$(TARGET) : test_layers.o Layers.o Mat2d.hpp.gch
	$(CC) $(CFLAGS) -o $(TARGET) test_layers.o Layers.o

test_layers.o : test_layers.cpp Mat2d.hpp 
	$(CC) $(CFLAGS) -c test_layers.cpp

Layers.o : Layers.cpp Layers.hpp Mat2d.hpp
	$(CC) $(CFLAGS) -c Layers.cpp

Mat2d.hpp.gch : Mat2d.hpp
	$(CC) $(CFLAGS) -c Mat2d.hpp


#Tensor.o : Tensor.hpp Mat2d.hpp
#	$(CC) $(CFLAGS) -c Tensor.hpp

clean :
	\rm *.gch *.o
