#ifndef _OPTIM_H_
#define _OPTIM_H_

#include <vector>

class Optim {
public:
    Optim(float lr);
    ~Optim();

    void set_params(vector<Mat2d<float>*> params);
    void set_grads(vector<Mat2d<float>*> params);
    void zero_grad();
    void update();

private:
    vector<Mat2d<float>*> params;
    vector<Mat2d<float>*> grads;
    float lr;
};

#endif 
