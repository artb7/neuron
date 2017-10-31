CC = g++
CFLAGS = -W -Wall -g -std=c++17
TARGET = main 

#$(TARGET) : test_mat2d.o Mat2d.hpp.gch
#	$(CC) $(CFLAGS) -o $(TARGET) test_mat2d.o

#$(TARGET) : test_layers.o Mat2d.hpp.gch Layers.o
#	$(CC) $(CFLAGS) -o $(TARGET) test_layers.o Layers.o


$(TARGET) : test_mlp.o Layers.o Mat2d.hpp.gch MLP.o
	$(CC) $(CFLAGS) -o $(TARGET) test_mlp.o Layers.o MLP.o

$(TARGET) : main.o test_layers

test_layers.o : test_layers.cpp Layers.hpp Mat2d.hpp 
	$(CC) $(CFLAGS) -c test_layers.cpp

test_mat2d.o : test_mat2d.cpp Mat2d.hpp 
	$(CC) $(CFLAGS) -c test_mat2d.cpp

test_mlp.o : test_mlp.cpp MLP.hpp
	$(CC) $(CFLAGS) -c test_mlp.cpp

Layers.o : Layers.cpp Layers.hpp Mat2d.hpp
	$(CC) $(CFLAGS) -c Layers.cpp

MLP.o : MLP.cpp MLP.hpp Layers.hpp
	$(CC) $(CFLAGS) -c MLP.cpp

Mat2d.hpp.gch : Mat2d.hpp
	$(CC) $(CFLAGS) -c Mat2d.hpp

#Tensor.o : Tensor.hpp Mat2d.hpp
#	$(CC) $(CFLAGS) -c Tensor.hpp

clean :
	\rm *.gch *.o
