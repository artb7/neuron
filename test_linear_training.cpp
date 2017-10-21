#include <iostream>

#include "Layers.hpp"
#include "Mat2d.hpp"

int main() {
    float x_data[4 * 2] = {0, 0, 0, 1, 1, 0, 1, 1}; 
    int y_data[4 * 1] = {0, 1, 1, 0};
    auto X = Mat2d<float>(4, 2, x_data);
    auto Y = Mat2d<int>(4, 1, y_data);
    
    float alpha = 1e-2; 

    Linear layer0 = Linear(2, 2);
    LeakyReLU l_relu = LeakyReLU();
    SoftmaxWithLoss criterion = SoftmaxWithLoss();
    
    for (int step = 0; step < 1000; ++step) {
        auto output = layer0.forward(X);
        output = l_relu.forward(output);

        auto loss = criterion.forward(output, Y);
        
        auto dout = loss.backward(
    }
    
    return 0;
};
