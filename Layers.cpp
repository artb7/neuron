#include "Layers.hpp"


void tensor_print(Mat2d t) {
	uint32_t dim0 = t.get_row();
	uint32_t dim1 = t.get_col();
	for (int i = 0; i < (int)dim0; ++i) {
		for (int j = 0; j < (int)dim1; ++j) {
			std::cout << t(i, j) << " ";	
		}
		std::cout << std::endl;
	}
	return;
}

Linear::Linear(uint32_t in_dim, uint32_t out_dim) {
    //TODO weight initialization
    float* weight_init_data = new float[in_dim * out_dim];
    for (int i = 0; i < (int)(in_dim * out_dim); ++i)
        weight_init_data[i] = 1.0;

    float* bias_init_data = new float[out_dim];
    for (int i = 0; i < (int)out_dim; ++i)
        bias_init_data[i] = 1.0;

    this->weight = Mat2d(in_dim, out_dim, weight_init_data);
    this->bias = Mat2d(1, out_dim, bias_init_data);
}
Linear::~Linear() {
}

Mat2d Linear::forward(Mat2d& x) {
    assert (x.get_col() == (this->weight).get_row());
    this->x = x;   
    Mat2d out = x.dot(this->weight) + this->bias;

    return out;
}

Mat2d Linear::backward(Mat2d& dout) {
    Mat2d dx = dout.dot((this->weight).T());  
    this->db = dout.sum(0); 
    this->dW = ((this->x).T()).dot(dout);

    /*
    std::cout << "Mat2d db: " << std::endl;
    tensor_print(this->db);
    std::cout << "Mat2d dW: " << std::endl;
    tensor_print(this->dW);
    */

    return dx;
}


LeakyReLU::LeakyReLU() {
    //this->mask = nullptr;
}
LeakyReLU::~LeakyReLU() {
}

Mat2d LeakyReLU::forward(Mat2d& x) {

    this->mask = (x <= 0);
    //std::cout << "hello" << std::endl;
    // TODO more simple 
    Mat2d out = x;
    Mat2d neg_result = out[this->mask] * 0.2;
    Mat2d reverse_mask = reverse_boolean(this->mask);
    Mat2d pos_result = out[reverse_mask];
    return neg_result + pos_result;
}

Mat2d LeakyReLU::backward(const Mat2d& d) {

    //dx[this->mask] = dx[this->mask] * 0.2;
    Mat2d dx = d;
    Mat2d neg_result = dx[this->mask] * 0.2;
    Mat2d reverse_mask = reverse_boolean(this->mask);
    Mat2d pos_result = dx[reverse_mask];
    return neg_result + pos_result;
}


Sigmoid::Sigmoid() {
}
Sigmoid::~Sigmoid() {
}

Mat2d Sigmoid::forward(Mat2d& x) {
    this->out = (1. / (1. + exp(-x)));
    return this->out;
}
Mat2d Sigmoid::backward(const Mat2d& dout) {
    Mat2d dx = dout;
    return dx * this->out * (1.0 - this->out);
}

SoftmaxWithLoss::SoftmaxWithLoss() {
    
}

SoftmaxWithLoss::~SoftmaxWithLoss() {

}

float SoftmaxWithLoss::compute(Mat2d& output, int target) {
    //TODO : Consider batch learning
    //
    Mat2d logit = exp(output - output.max());
    Mat2d S = logit.sum();

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

Mat2d SoftmaxWithLoss::backward(const Mat2d& dout) {
    this->dout = dout;
    Mat2d dx = this->y;
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
