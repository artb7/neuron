#include "Layers.hpp"

Linear::Linear(uint32_t in_dim, uint32_t out_dim) {
    //TODO more efficient weight initialization
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(-1.0, 1.0);
    
    float* weight_init_data = new float[in_dim * out_dim];
    for (int i = 0; i < (int)(in_dim * out_dim); ++i)
        weight_init_data[i] = dis(gen);

    float* bias_init_data = new float[out_dim];
    for (int i = 0; i < (int)out_dim; ++i)
        bias_init_data[i] = dis(gen);

    this->weight = Mat2d<float>(in_dim, out_dim, weight_init_data);
    this->bias = Mat2d<float>(1, out_dim, bias_init_data);

    std::cout << std::endl;
    std::cout << "Mat2d<float> W: " << std::endl;
    (this->weight).print();
    std::cout << "Mat2d<float> b: " << std::endl;
    (this->bias).print();
    std::cout << std::endl;
}
Linear::~Linear() {
}

Mat2d<float> Linear::forward(Mat2d<float>& x) {
    assert (x.get_col() == (this->weight).get_row());
    this->x = x;   
    Mat2d<float> out = x.dot(this->weight) + this->bias;

    return out;
}

Mat2d<float> Linear::backward(Mat2d<float>& dout) {
    Mat2d<float> dx = dout.dot((this->weight).T());  
    this->db = dout.sum(0); 
    this->dW = ((this->x).T()).dot(dout);

    /*
    std::cout << std::endl;
    std::cout << "Mat2d<float> db: " << std::endl;
    (this->db).print();
    std::cout << "Mat2d<float> dW: " << std::endl;
    (this->dW).print();
    std::cout << std::endl;
    */

    return dx;
}


LeakyReLU::LeakyReLU() {
    //this->mask = nullptr;
}
LeakyReLU::~LeakyReLU() {
}

Mat2d<float> LeakyReLU::forward(Mat2d<float>& x) {

    this->mask = (x <= 0);
    //std::cout << "hello" << std::endl;
    // TODO more simple 
    Mat2d<float> out = x;
    Mat2d<float> neg_result = out[this->mask] * 0.2;
    Mat2d<float> reverse_mask = reverse_boolean(this->mask);
    Mat2d<float> pos_result = out[reverse_mask];
    return neg_result + pos_result;
}

Mat2d<float> LeakyReLU::backward(const Mat2d<float>& dout) {

    //dx[this->mask] = dx[this->mask] * 0.2;
    Mat2d<float> dx = dout;
    Mat2d<float> neg_result = dx[this->mask] * 0.2;
    Mat2d<float> reverse_mask = reverse_boolean(this->mask);
    Mat2d<float> pos_result = dx[reverse_mask];
    return neg_result + pos_result;
}


Sigmoid::Sigmoid() {
}
Sigmoid::~Sigmoid() {
}

Mat2d<float> Sigmoid::forward(Mat2d<float>& x) {
    this->out = ((float)1. / ((float)1. + exp(-x)));
    return this->out;
}
Mat2d<float> Sigmoid::backward(const Mat2d<float>& dout) {
    Mat2d<float> dx = dout;
    return dx * this->out * ((float)1.0 - this->out);
}

SoftmaxWithLoss::SoftmaxWithLoss() {
    
}

SoftmaxWithLoss::~SoftmaxWithLoss() {

}

float SoftmaxWithLoss::compute(Mat2d<float>& output, int target) {
    //TODO : Consider batch learning
    //
    Mat2d<float> logit = exp(output - output.max());
    Mat2d<float> S = logit.sum();

    this->y = logit / S(0, 0);
    this->t = target;
    float loss = -1 * std::log(y(target, 0) + 1e-7);

    /*
    std::cout << "output - output.max()" << std::endl;
    tensor_print(output - output.max());
    std::cout << "logit: " << std::endl;
    tensor_print(logit);
    std::cout << "S: " << std::endl;
    tensor_print(S);
    std::cout << "y: " << std::endl;
    tensor_print(this->y);
    std::cout << "loss: " << loss  << std::endl;
    */

    return loss;
}

Mat2d<float> SoftmaxWithLoss::backward(const Mat2d<float>& dout) {
    this->dout = dout;
    Mat2d<float> dx = this->y;
    dx(this->t, 0) = dx(this->t, 0) - 1.0;
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
