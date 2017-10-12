#include <iostream>

#include "Tensor.h"
#include "Layers.h"

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
        float inp_data[dim0 * dim1] = {0, 0, -5, 5};
	Tensor A(dim0, dim1, a_data);
	Tensor B(dim0, dim1, b_data);
        Tensor inp(dim0, dim1, inp_data);
	/*	
	std::cout << "Tensor A + B: " << std::endl;
	print(A + B);
	std::cout << "Tensor A * B: " << std::endl;
	print(A * B);
	std::cout << "Tensor A / B: " << std::endl;
	print(A / B);
	std::cout << "Tensor A > B: " << std::endl;
	print(A > B);	
	std::cout << "Tensor A >= B: " << std::endl;
	print(A >= B);	
	std::cout << "Tensor A < B: " << std::endl;
	print(A < B);	
	std::cout << "Tensor A <= B: " << std::endl;
	print(A <= B);	
	std::cout << "Tensor A = B: " << std::endl;
	A = B;
	print(A);	

	std::cout << "Tensor A - B: " << std::endl;
        Tensor D = A - B;
	print(D);
        LeakyReLU l_relu = LeakyReLU();
	std::cout << "Tensor forward of LeakyReLU(A - B) : " << std::endl;
	print(l_relu.forward(D));
	std::cout << "Tensor backward of LeakyReLU(A - B) when d = 1 : " << std::endl;
	print(l_relu.backward(A));

	std::cout << "Tensor inp: " << std::endl;
	print(inp);
        Sigmoid sigmoid = Sigmoid();
	std::cout << "Tensor forward of sigmoid(inp) : " << std::endl;
	print(sigmoid.forward(inp));
	std::cout << "Tensor backward of sigmoid(inp) when d = 1 : " << std::endl;
	print(sigmoid.backward(A));
	*/



	return 0;
}
