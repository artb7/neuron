#include <iostream>


int main() {
    float apple = 100;
    float orange = 150;
    float num_apple = 2;
    float num_orange = 3;
    float tax = 1.1;

    // layers
    MulLayer mul_apple_layer;
    MulLayer mul_orange_layer;
    AddLayer add_layer;
    MulLayer mul_tax_layer;
    

    // forward
    float apple_price = mul_apple_layer.forward(apple, num_apple);
    float orange_price = mul_orange_layer.forward(orange, num_orange);
    float price_before_tax = add_layer.forward(apple_price, orange_price);
    float price = mul_tax_layer.forward(price_before_tax, tax);

    // backward
    float dprice = 1;
    Result_backward d1 = mul_tax_layer.backward(dprice); 
    Result_backward d2 = add_layer.backward(d1.grad[0]);
    Result_backward d3 = mul_apple_layer.backward(d2.grad[0]);
    Result_backward d4 = mul_orange_layer.backward(d2.grad[1]);
    float dtax = d1.grad[1]; 
    float dapple = d3.grad[0];
    float dnum_apple = d3.grad[1];
    float dorange = d4.grad[0];
    float dnum_orange = d4.grad[1];

    std::cout << "price : " << price << std::endl;
    std::cout << "dapple : " << dapple << std::endl;
    std::cout << "dnum_apple : " << dnum_apple << std::endl;
    std::cout << "dorange: " << dorange << std::endl;
    std::cout << "dnum_orange: " << dnum_orange << std::endl;
    std::cout << "dtax : " << dtax << std::endl;

    return 0;
}

