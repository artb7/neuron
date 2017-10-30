#ifndef _MODEL_H_
#define _MODEL_H_

#include <vector>

#include "Layers.hpp"

class Model {
public:
    Model();
    ~Model();

    Mat2d<float> operator(Mat2d<float>& x); 
    void backward();

    void connect_with_optimizer(Optim& optim);
    void connect_with_criterion(Layer& criterion);

    //bool check_is_feasible()

private:
    std::vector<Layer*> module;  
    std::vector<Mat2d<float>*> params;  
    std::vector<Mat2d<float>*> grads;  

    Optim* optim;
    Layer* criterion;
};

#endif //_MODEL_H_


