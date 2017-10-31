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
    virtual bool has_params() = 0;

private:
};


class Linear : public Layer {
public:
    Linear(uint32_t in_dim, uint32_t out_dim);
    ~Linear();

    virtual Mat2d<float> forward(const Mat2d<float>& x);
    virtual Mat2d<float> backward(const Mat2d<float>& dout);
    virtual bool has_params();

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
    virtual bool has_params();

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
    virtual bool has_params();

private:
    Mat2d<float> out;
};


class Add_block : public Layer{
public:
	Add_block(uint32_t num_branch);
	virtual ~Add_block();

	virtual Mat2d<float> forward(const Mat2d<float>& x);
	virtual Mat2d<float> backward(const Mat2d<float>& dout);
    virtual bool has_params();

    void add(Sequential* layers);

private:
    uint32_t num_branch;
    vector<Sequential*> branches;
    //Sequential* branches;
    uint32_t in_row;
    uint32_t in_col;
};

class Sequential : public Layer {
public:
	Sequential(uint32_t num_layer);
	virtual ~Sequential();

	virtual Mat2d<float> forward(const Mat2d<float>& x);
	virtual Mat2d<float> backward(const Mat2d<float>& dout);
    virtual bool has_params();

    void add(Layer* layer);

private:
    uint32_t num_layer;
    vector<Layer*> layers;
    //Layer* layers;
};
//TODO mul_block, cat_block

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
