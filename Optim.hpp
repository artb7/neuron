#ifndef _OPTIM_H_
#define _OPTIM_H_

#include <vector>

class Optim {
public:
    Optim();
    ~Optim();

    update();

private:
    vector<Mat2d<float>*> params;
    vector<Mat2d<float>*> grads;
    float lr;
};

#endif 
