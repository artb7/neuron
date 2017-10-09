#include <iostream>

#include "Tensor.h"

void print(Tensor t) {
	uint32_t dim0 = t.get_dim0();
	uint32_t dim1 = t.get_dim1();
	for (int i = 0; i < (int)dim0; ++i) {
		for (int j = 0; j < (int)dim1; ++j) {
			std::cout << t(i, j) << " ";	
		}
		std::cout << std::endl;
	}
	return;
}

int main() {

	uint32_t dim0 = 2, dim1 = 2;
	float a_data[dim0 * dim1] = {1, 1, 1, 1};
	float b_data[dim0 * dim1] = {0, 1, 2, 3};
	Tensor A(dim0, dim1, a_data);
	Tensor B(dim0, dim1, b_data);
	/*	
	std::cout << "Tensor A + B: " << std::endl;
	print(A + B);
	std::cout << "Tensor A - B: " << std::endl;
	print(A - B);
	std::cout << "Tensor A * B: " << std::endl;
	print(A * B);
	std::cout << "Tensor A / B: " << std::endl;
	print(A / B);
	*/
	
	std::cout << "Tensor A : " << std::endl;
	print(A);
	std::cout << "Tensor B : " << std::endl;
	print(B);
	Tensor C = A.matmul(B);
	std::cout << "Tensor A.matmul(B) : " << std::endl;
	print(C);

	/*
	std::cout << "Tensor A > B: " << std::endl;
	print(A > B);	
	std::cout << "Tensor A >= B: " << std::endl;
	print(A >= B);	
	std::cout << "Tensor A < B: " << std::endl;
	print(A < B);	
	std::cout << "Tensor A <= B: " << std::endl;
	print(A <= B);	
	A = B;
	std::cout << "Tensor A = B: " << std::endl;
	print(A);	
	*/
	return 0;
}
