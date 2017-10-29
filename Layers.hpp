#ifndef _LAYER_H_
#define _LAYER_H_

#include <cmath>
#include <iostream>
#include <random>
#include <stdint.h>

#include "Mat2d.hpp"


//TODO make use of heap and release resource
class Layer {
public:
	Layer();
	virtual ~Layer();

	virtual Mat2d<float> forward(const Mat2d<float>& x) = 0;
	virtual Mat2d<float> backward(const Mat2d<float>& dout) = 0;

private:
};


class Linear : public Layer {
public:
    Linear(uint32_t in_dim, uint32_t out_dim);
    ~Linear();

    Mat2d<float> forward(const Mat2d<float>& x);
    Mat2d<float> backward(const Mat2d<float>& dout);

    Mat2d<float>* get_pWeight();
    Mat2d<float>* get_pBias();
    Mat2d<float> get_dW();
    Mat2d<float> get_db();

private:
    Mat2d<float> weight;
    Mat2d<float> bias;
    Mat2d<float> dW;
    Mat2d<float> db;
    Mat2d<float> x;
};


class LeakyReLU : public Layer {
public:
    LeakyReLU();
    ~LeakyReLU();

    Mat2d<float> forward(const Mat2d<float>& x);
    Mat2d<float> backward(const Mat2d<float>& dout);

private:
    //TODO float mask no problem?
    Mat2d<float> mask;
};


class Sigmoid : public Layer {
public:
    Sigmoid();
    ~Sigmoid();

    Mat2d<float> forward(const Mat2d<float>& x);
    Mat2d<float> backward(const Mat2d<float>& dout);

private:
    Mat2d<float> out;
};

class SoftmaxWithLoss {
public:
    SoftmaxWithLoss();
    ~SoftmaxWithLoss();
    //TODO float target ?
    Mat2d<float> compute(const Mat2d<float>& output, const Mat2d<float>& target);
    Mat2d<float> backward(const Mat2d<float>& dout);

private:    
    Mat2d<float> dout;
    Mat2d<float> t;
    Mat2d<float> y;
};

#endif //_LAYER_H_
