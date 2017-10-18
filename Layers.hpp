#ifndef _LAYER_H_
#define _LAYER_H_

#include <cmath>
#include <stdint.h>
#include "Tensor.hpp"
/*
class Layer {
public:
	Layer();
	~Layer();

	Tensor forward(const Tensor& x);
	Tensor backward(const Tensor& d);

private:
};
*/

class Linear {
public:
    Linear(uint32_t in_dim, uint32_t out_dim);
    ~Linear();

    Tensor forward(Tensor& x);
    Tensor backward(Tensor& dout);

private:
    Tensor weight;
    Tensor bias;
    Tensor x;
    Tensor dW;
    Tensor db;
};

class LeakyReLU {
public:
    LeakyReLU();
    ~LeakyReLU();

    Tensor forward(Tensor& x);
    Tensor backward(const Tensor& dout);

private:
    Tensor mask;
};


class Sigmoid {
public:
    Sigmoid();
    ~Sigmoid();

    Tensor forward(Tensor& x);
    Tensor backward(const Tensor& dout);

private:
    Tensor out;
};

class SoftmaxWithLoss {
public:
    SoftmaxWithLoss();
    ~SoftmaxWithLoss();
    float compute(Tensor& output, int target);
    Tensor backward(const Tensor& dout);

private:    
    Tensor y;
    int t;
    Tensor dout;
};

#endif //_LAYER_H_
