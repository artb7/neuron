#ifndef _LAYER_H_
#define _LAYER_H_

#include <cmath>
#include <iostream>
#include <stdint.h>
#include "Mat2d.hpp"

/*
class Layer {
public:
	Layer();
	~Layer();

	Mat2d forward(const Mat2d& x);
	Mat2d backward(const Mat2d& d);

private:
};
*/

class Linear {
public:
    Linear(uint32_t in_dim, uint32_t out_dim);
    ~Linear();

    Mat2d forward(Mat2d& x);
    Mat2d backward(Mat2d& dout);

private:
    Mat2d weight;
    Mat2d bias;
    Mat2d x;
    Mat2d dW;
    Mat2d db;
};

class LeakyReLU {
public:
    LeakyReLU();
    ~LeakyReLU();

    Mat2d forward(Mat2d& x);
    Mat2d backward(const Mat2d& dout);

private:
    Mat2d mask;
};


class Sigmoid {
public:
    Sigmoid();
    ~Sigmoid();

    Mat2d forward(Mat2d& x);
    Mat2d backward(const Mat2d& dout);

private:
    Mat2d out;
};

class SoftmaxWithLoss {
public:
    SoftmaxWithLoss();
    ~SoftmaxWithLoss();
    float compute(Mat2d& output, int target);
    Mat2d backward(const Mat2d& dout);

private:    
    Mat2d y;
    int t;
    Mat2d dout;
};

#endif //_LAYER_H_
