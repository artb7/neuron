#include "MLP.hpp"


MLP::MLP() {}

MLP::MLP(uint32_t in_dim, uint32_t hidden_dim, uint32_t out_dim) {
    Linear layer0 = Linear(in_dim, hidden_dim);
    Linear layer1 = Linear(hidden_dim, out_dim);
    LeakyReLU l_relu = LeakyReLU();
    module.push_back(layer0);
    module.push_back(l_relu);
    module.push_back(layer1);
}

MLP::~MLP() {
    //TODO release resource
}

auto MLP::predict(Mat2d<float> x) {
    Mat2d<float> out = x;
    for (int i = 0; i < moduel.size(); ++i) {
        out = module[i].forward(out);
    }
    return out;
}

auto MLP::loss(Mat2d<float> x, Mat2d<float> t) {
    Mat2d<float> out = predict(x);
    return criterion(out, t); 
}

auto MLP::numerical_gradient(Mat2d<float> x, Mat2d<float> t) {

}

auto MLP::gradient(Mat2d<float> x, Mat2d<float> t){
    loss(x, t);

    Mat2d<float> dout = Mat2d<float> 
}
