#ifndef _LAYER_H_
#define _LAYER_H_

#include <cmath>
#include <iostream>
#include <random>
#include <stdint.h>

#include "Mat2d.hpp"


//TODO make use of hepa and release resource
class Layer {
public:
	Layer();
	~Layer();

	virtual Mat2d<float> forward(const Mat2d<float>& x) = 0;
	virtual Mat2d<float> backward(const Mat2d<float>& dout) = 0;

private:
};


class Linear : public {
public:
    Linear(uint32_t in_dim, uint32_t out_dim);
    ~Linear();

    Mat2d<float> forward(Mat2d<float>& x);
    Mat2d<float> backward(Mat2d<float>& dout);

private:
    Mat2d<float> weight;
    Mat2d<float> bias;
    Mat2d<float> dW;
    Mat2d<float> db;
    Mat2d<float> x;
};


class LeakyReLU : public {
public:
    LeakyReLU();
    ~LeakyReLU();

    Mat2d<float> forward(Mat2d<float>& x);
    Mat2d<float> backward(const Mat2d<float>& dout);

private:
    //TODO float mask no problem?
    Mat2d<float> mask;
};


class Sigmoid : public {
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
    int t;
    Mat2d<float> dout;
    Mat2d<float> y;
};

#endif //_LAYER_H_
