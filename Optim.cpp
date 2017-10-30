#include "Optim.hpp"

Optim::Optim(float lr) {
    this->lr = lr; 
}
Optim::~Optim() {
}

void set_params(vector<Mat2d<float>*> params) {

}

void set_grads(vector<Mat2d<float>*> grads) {
 
}

void Optim::zero_grad() {
    for (int i = 0; i < (int)grads.size(); ++i) {
        grads[i]->fill_zeros(); 
    }
}

void Optim::update() {
    for (int i = 0; i < params.size(); ++i) {
        (*params[i]) = (*params[i]) - (lr * (*grads[i]));
    }
}
