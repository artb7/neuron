#ifndef _LAYER_H_
#define _LAYER_H_

#include <cmath>
#include <iostream>
#include <random>
#include <stdint.h>

#include "Mat2d.hpp"

/*
class Layer {
public:
	Layer();
	~Layer();

	Mat2d<float> forward(const Mat2d<float>& x);
	Mat2d<float> backward(const Mat2d<float>& d);

private:
};
*/

class Linear {
public:
    Linear(uint32_t in_dim, uint32_t out_dim);
    ~Linear();

    Mat2d<float> forward(Mat2d<float>& x);
    Mat2d<float> backward(Mat2d<float>& dout);

private:
    Mat2d<float> weight;
    Mat2d<float> bias;
    Mat2d<float> x;
    Mat2d<float> dW;
    Mat2d<float> db;
};


class LeakyReLU {
public:
    LeakyReLU();
    ~LeakyReLU();

    Mat2d<float> forward(Mat2d<float>& x);
    Mat2d<float> backward(const Mat2d<float>& dout);

private:
    //TODO float mask no problem?
    Mat2d<float> mask;
};


class Sigmoid {
public:
    Sigmoid();
    ~Sigmoid();

    Mat2d<float> forward(Mat2d<float>& x);
    Mat2d<float> backward(const Mat2d<float>& dout);

private:
    Mat2d<float> out;
};

class SoftmaxWithLoss {
public:
    SoftmaxWithLoss();
    ~SoftmaxWithLoss();
    float compute(Mat2d<float>& output, int target);
    Mat2d<float> backward(const Mat2d<float>& dout);

private:    
    Mat2d<float> y;
    int t;
    Mat2d<float> dout;
};

#endif //_LAYER_H_
