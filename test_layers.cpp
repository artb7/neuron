#include "test_layers.hpp"

void test_LeakyReLU() {

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
}

void test_Sigmoid() {

    float inp_data[2 * 3] = {0, 0, -5, 5, 1, -1};
    float dout_data[2 * 3] = {1, 1, 1, 1, 1, 1};

    Mat2d<float> inp(2, 3, inp_data);
    Mat2d<float> dout(2, 3, dout_data);
    
    // [Test] sigmoid 
    Sigmoid sigmoid = Sigmoid();
    std::cout << "inp: " << std::endl;
    inp.print();
    std::cout << "forward of sigmoid(inp) : " << std::endl;
    (sigmoid.forward(inp)).print();
    std::cout << "backward of sigmoid(inp) when d = 1 : " << std::endl;
    (sigmoid.backward(dout)).print();
    std::cout << std::endl;
}

void test_Linear() {
    
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
}

void test_SoftmaxWithLoss() {

    // [Test] softmax 
    int batch_size = 2;
    float out_data[batch_size * 10] = {
        0.1, 0.05, 0.9, 0.0, 0.05, 0.1, 0.0, 0.1, 0.0, 0.0, 
        0.1, 0.05, 0.1, 0.0, 0.05, 0.1, 0.0, 0.9, 0.0, 0.0
    };
    float target_data[batch_size] = {2, 2};
    float dout_data[1] = {1};

    Mat2d<float> output(batch_size, 10, out_data);
    Mat2d<float> target(batch_size, 1, target_data);
    Mat2d<float> dout(1, 1, dout_data);

    SoftmaxWithLoss criterion = SoftmaxWithLoss();
    std::cout << "Mat2d output: " << std::endl;
    output.print();
    std::cout << "Mat2d target: " << std::endl;
    target.print();
    std::cout << "Mat2d criterion.compute(output, target): " << std::endl;
    std::cout << criterion.compute(output, target) << std::endl;
    std::cout << "Mat2d criterion.backward(dout = 1): " << std::endl;
    (criterion.backward(dout)).print();
    std::cout << std::endl;
}
