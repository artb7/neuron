#ifndef _MLP_H_
#define _MLP_H_

#include <stdexcept>
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

    Mat2d<float> predict(Mat2d<float>& x);
    Mat2d<float> loss(Mat2d<float>& x, Mat2d<float>& t);
    //auto accuracy(Mat2d<float> x, Mat2d<float> t);
    std::vector<std::tuple<std::string, Mat2d<float>>> numerical_gradient(Mat2d<float>& x, Mat2d<float>& t);
    std::vector<std::tuple<std::string, Mat2d<float>>> gradient(Mat2d<float>& x, Mat2d<float>& t);

    std::vector<std::tuple<std::string, Mat2d<float>*>> get_params();
    void zero_grad();
    void update_params(float lr);

private:
    //TODO: Why std::vector? how to make hash-table for module and gradient
    Mat2d<float> numerical_gradient(std::string name, Mat2d<float>& x, Mat2d<float>& t);
    std::vector<std::tuple<std::string, Layer*>> module;
    std::vector<std::tuple<std::string, Mat2d<float>*>> params;
    std::vector<std::tuple<std::string, Mat2d<float>>> grads;
    std::vector<std::tuple<std::string, Mat2d<float>>> numerical_grads;
    SoftmaxWithLoss criterion;
    uint32_t in_dim;
    uint32_t hidden_dim;
    uint32_t out_dim;
};

#endif //_MLP_H_
