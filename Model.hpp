#ifndef _MODEL_H_
#define _MODEL_H_

#include <vector>

class Model {
public:
    Model();
    ~Model();

    Mat2d<float> operator(Mat2d<float>& x);
    void backward();

    void connect_with_optimizer();
    void connect_with_criterion();

    bool check_is_feasible()

private:
    std::vector<Layer*> module;
};

#endif //_MODEL_H_


