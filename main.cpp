#include <iostream>

#include "Tensor.hpp"
#include "Layers.hpp"

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
        //float out_data[10] = {0.1, 0.05, 0.6, 0.0, 0.05, 0.1, 0.0, 0.1, 0.0, 0.0};
        float out_data[10] = {0.1, 0.05, 0.1, 0.0, 0.05, 0.1, 0.0, 0.6, 0.0, 0.0};
        float dout_data[2 * 3] = {1, 1, 1, 1, 1, 1};
        float one_data[2] = {1, 2};

	Tensor A(dim0, dim1, a_data);
	Tensor B(dim0, dim1, b_data);
        Tensor onedim(1, 2, one_data);
        Tensor output(10, 1, out_data);
        Tensor dout(2, 3, dout_data);

        /*
	std::cout << "Tensor A: " << std::endl;
	print(A);
        A(0,0) = 0;
	std::cout << "Tensor A: " << std::endl;
	print(A);
        */

        /*
	std::cout << "Tensor A + onedim: " << std::endl;
	print(A + onedim);
	std::cout << "Tensor A + onedim.T(): " << std::endl;
	print(A + onedim.T());
        */

        /*
	uint32_t dim0_t = 2, dim1_t = 4;
        float t_data_1[dim0_t * dim1_t] = {1,2,3,4,5,6,7,8};
        float t_data_2[dim0_t * dim1_t] = {1,2,3,4,5,6,7,8};
        Tensor t1(dim0_t, dim1_t, t_data_1);
        Tensor t2(dim1_t, dim0_t, t_data_2);

	std::cout << "Tensor t1: " << std::endl;
        print(t1);
	std::cout << "Tensor t1.sum(0): " << std::endl;
        print(t1.sum(0));
	std::cout << "Tensor t1.sum(1): " << std::endl;
        print(t1.sum(1));

	std::cout << "Tensor t1: " << std::endl;
        print(t1);
	std::cout << "Tensor t2: " << std::endl;
        print(t2);
	std::cout << "Tensor t1.T(): " << std::endl;
	print(t1.T());
	std::cout << "Tensor t1.dot(t1.T()): " << std::endl;
	print(t1.dot(t1.T()));
        */

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
        
        /*
	std::cout << "Tensor inp: " << std::endl;
	print(inp);
        Linear linear = Linear(2, 3);
	std::cout << "Tensor forward of linear(inp) : " << std::endl;
	print(linear.forward(inp));
	std::cout << "Tensor backward of linear(inp) when d = 1 : " << std::endl;
	print(linear.backward(dout));
        */

        SoftmaxWithLoss criterion = SoftmaxWithLoss();
        int target = 2;
	std::cout << "Tensor output: " << std::endl;
	print(output);
	std::cout << "Tensor target: " << std::endl;
        std::cout << target << std::endl;
	std::cout << "Tensor criterion.compute(output, target): " << std::endl;
        std::cout << criterion.compute(output, target) << std::endl;
	std::cout << "Tensor criterion.backward(): " << std::endl;
	print(criterion.backward(A));



	return 0;
}
