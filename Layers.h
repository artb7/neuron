#ifndef _LAYER_H_
#define _LAYER_H_

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

	Tensor forward(const Tensor& x);
	Tensor backward(const Tensor& d);

private:
	Tensor weight;
	Tensor bias;
	Tensor input;
};

class LeakyReLU {
public:
	LeakyReLU();
	~LeakyReLU();

	Tensor forward(const Tensor& x);
	Tensor backward(const Tensor& d);

private:
	Tensor mask;
};

#endif _LAYER_H_

