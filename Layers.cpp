#include "Layers.h"
/*
Linear::Linear(uint32_t in_dim, uint32_t out_dim) {
    float* weight_zero_data = new float[in_dim * out_dim];
    for (int i = 0; i < in_dim * out_dim; ++i)
        weight_zero_data[i] = 0;

    float* bias_zero_data = new float[out_dim];
    for (int i = 0; i < out_dim; ++i)
        bias_zero_data[i] = 1;

    this->weight = Tensor(in_dim, out_dim, weight_zero_data)
    this->bias = Tensor(in_dim, out_dim, bias_zero_data)
    this->input = Tensor(in_dim, out_dim)
}
*/

LeakyReLU::LeakyReLU() {
}
LeakyReLU::~LeakyReLU() {
}

Tensor LeakyReLU::forward(const Tensor& x) {
    this->mask = (x <= 0);
    Tensor out = x;
    out[this->mask] = out[this->mask] * 0.2;
    return out;
}

Tensor LeakyReLU::backward(const Tensor& d) {
    Tensor dx = d;
    dx[this->mask] = dx[this->mask] * 0.2;
    return dx;
}

/*
MulLayer::MulLayer(){
    this->x = 0.0;
    this->y = 0.0;
    this->result_backward.size = 2;
    this->result_backward.grad = new float[2];
}
MulLayer::~MulLayer(){}

float MulLayer::forward(float x, float y){
    this->x = x;
    this->y = y;
    float out = x * y; 
    return out;
}

struct Result_backward MulLayer::backward(float dout){
    float dx = dout * this->y;
    float dy = dout * this->x;   
    this->result_backward.grad[0] = dx;
    this->result_backward.grad[1] = dy;
  
    return this->result_backward;
}

AddLayer::AddLayer(){
    this->x = 0.0;
    this->y = 0.0;
    this->result_backward.size = 2;
    this->result_backward.grad = new float[2];
}
AddLayer::~AddLayer(){}

float AddLayer::forward(float x, float y){
    this->x = x;
    this->y = y;
    float out = x + y; 
    return out;
}

struct Result_backward AddLayer::backward(float dout){
    float dx = dout * 1;
    float dy = dout * 1;
    this->result_backward.grad[0] = dx;
    this->result_backward.grad[1] = dy;
  
    return this->result_backward;
}
*/
