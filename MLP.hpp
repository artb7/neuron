#ifndef _MLP_H_
#define _MLP_H_

#include <tuple>
#include <vector>

#include "Layers.hpp"
//#include "Parameter.hpp"

class MLP {
public:
    //MLP();
    MLP(uint32_t in_dim, uint32_t hidden_dim, uint32_t out_dim);
    ~MLP();

    auto predict(Mat2d<float> x);
    auto loss(Mat2d<float> x, Mat2d<float> t);
    //auto accuracy(Mat2d<float> x, Mat2d<float> t);
    auto numerical_gradient(Mat2d<float> x, Mat2d<float> t);
    auto gradient(Mat2d<float> x, Mat2d<float> t);

prviate:
    vector<Layer*> module;
    SoftmaxWithLoss criterion;
    uint32_t in_dim;
    uint32_t hidden_dim;
    uint32_t out_dim;
};

#endif //_MLP_H_
