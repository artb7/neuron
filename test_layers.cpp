#include <iostream>

#include "Mat2d.hpp"
#include "Layers.hpp"


int main() {

    float inp_data[2 * 3] = {0, 0, -5, 5, 1, -1};
    float dout_data[2 * 3] = {1, 1, 1, 1, 1, 1};

    Mat2d<float> inp(2, 3, inp_data);
    Mat2d<float> dout(2, 3, dout_data);

    // [Test] LeakyReLU
    LeakyReLU l_relu = LeakyReLU();
    std::cout << "Mat2d inp" << std::endl;
    inp.print();
    std::cout << "Mat2d forward of LeakyReLU(inp) : " << std::endl;
    (l_relu.forward(inp)).print();
    std::cout << "Mat2d backward of LeakyReLU(inp) when dout = 1 : " << std::endl;
    (l_relu.backward(dout)).print();
    std::cout << std::endl;

    // [Test] sigmoid 
    Sigmoid sigmoid = Sigmoid();
    std::cout << "Mat2d inp: " << std::endl;
    inp.print();
    std::cout << "Mat2d forward of sigmoid(inp) : " << std::endl;
    (sigmoid.forward(inp)).print();
    std::cout << "Mat2d backward of sigmoid(inp) when d = 1 : " << std::endl;
    (sigmoid.backward(dout)).print();
    std::cout << std::endl;

    // [Test] linear 
    float inp_data_linear[4 * 2] = {0, 0, 0, 1, 1, 0, 1, 1};
    float dout_data_linear[4 * 2] = {1, 1, 1, 1, 1, 1, 1, 1};
    Mat2d<float> inp_linear(4, 2, inp_data_linear);
    Mat2d<float> dout_linear(4, 2, dout_data_linear);

    Linear linear = Linear(2, 2);
    std::cout << "Mat2d inp: " << std::endl;
    inp_linear.print();
    std::cout << "Mat2d forward of linear(inp) : " << std::endl;
    (linear.forward(inp_linear)).print();
    std::cout << "Mat2d backward of linear(inp) when d = 1 : " << std::endl;
    (linear.backward(dout_linear)).print();
    std::cout << std::endl;

    // [Test] softmax 
    //float out_data[10] = {0.1, 0.05, 0.6, 0.0, 0.05, 0.1, 0.0, 0.1, 0.0, 0.0};
    float out_data[10] = {0.1, 0.05, 0.1, 0.0, 0.05, 0.1, 0.0, 0.6, 0.0, 0.0};
    Mat2d<float> output(10, 1, out_data);
    int target = 2;

    SoftmaxWithLoss criterion = SoftmaxWithLoss();
    std::cout << "Mat2d output: " << std::endl;
    output.print();
    std::cout << "Mat2d target: " << std::endl;
    std::cout << target << std::endl;
    std::cout << "Mat2d criterion.compute(output, target): " << std::endl;
    std::cout << criterion.compute(output, target) << std::endl;
    std::cout << "Mat2d criterion.backward(dout = 1): " << std::endl;
    (criterion.backward(dout)).print();
    std::cout << std::endl;

    return 0;
}
