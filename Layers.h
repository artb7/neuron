#ifndef _LAYER_H_
#define _LAYER_H_

#include <cmath>
#include <stdint.h>
#include "Tensor.h"
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
    Tensor backward(Tensor& d);

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
    Tensor backward(const Tensor& d);

private:
    Tensor mask;
};


class Sigmoid {
public:
    Sigmoid();
    ~Sigmoid();

    Tensor forward(Tensor& x);
    Tensor backward(const Tensor& d);

private:
    Tensor out;
};

#endif //_LAYER_H_
