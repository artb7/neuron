#ifndef _MLP_H_
#define _MLP_H_

#include <string>
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

    void zero_grad();

private:
    //TODO: how to make hash-table for module and gradient 
    std::vector<Layer*> module;
    std::vector<std::tuple<std::string, Mat2d<float>*>> grads;
    SoftmaxWithLoss criterion;
    uint32_t in_dim;
    uint32_t hidden_dim;
    uint32_t out_dim;
};

#endif //_MLP_H_
