#include "MLP.hpp"

MLP::MLP(uint32_t in_dim, uint32_t hidden_dim, uint32_t out_dim) {
    this->in_dim = in_dim;
    this->hidden_dim = hidden_dim;
    this->out_dim = out_dim;
    Layer *layer0 = new Linear(in_dim, hidden_dim);
    Layer *layer1 = new Linear(hidden_dim, out_dim);
    LeakyReLU *l_relu = new LeakyReLU();
    module.push_back(layer0);
    module.push_back(l_relu);
    module.push_back(layer1);
    
    auto grad = std::make_tuple("W0", Mat::zeros(in_dim, hidden_dim));
    grads.push_back(grad);
    grad = std::make_tuple("b0", Mat::zeros(1, hidden_dim));
    grads.push_back(grad);
    grad = std::make_tuple("W1", Mat::zeros(hidden_dim, out_dim));
    grads.push_back(grad);
    grad = std::make_tuple("b1", Mat::zeros(1, out_dim));
    grads.push_back(grad);
}

MLP::~MLP() {
    //TODO release resource
}

Mat2d<float> MLP::predict(Mat2d<float>& x) {
    Mat2d<float> out = x;
    for (int i = 0; i < (int)module.size(); ++i) {
        out = module[i]->forward(out);
    }
    return out;
}

float MLP::loss(Mat2d<float>& x, Mat2d<float>& t) {
    Mat2d<float> out = predict(x);
    return criterion.compute(out, t); 
}

Mat2d<float> MLP::numerical_gradient(Mat2d<float>& x, Mat2d<float>& t) {
    //TODO : make
    return x + t;
}
Mat2d<float> MLP::gradient(Mat2d<float>& x, Mat2d<float>& t){
    loss(x, t);
    Mat2d<float> dout = Mat::ones(t.get_row(), this->out_dim);

    for (int i = module.size() - 1; i >= 0; --i) {
        dout = module[i]->backward(dout);
    }
    return x;    
}

void MLP::zero_grad() {
    
    /*
    for (int i = 0; i < grads.size(); ++i) {
        grad = std::get<1>(grads[i]);
        grad = 0;
    }
    */

    /*
    Mat2d<float>* pW; 
    Mat2d<float>* pb;
    uint32_t in_dim = 0;
    uint32_t out_dim = 0;
    std::string weight_name = "W";
    std::string bias_name = "b";
    for (int i = 0; i < (int)module.size(); ++i) {
        Linear* pLinear = dynamic_cast<Linear*>(module[i]);
        if (!pLinear) 
            throw std::runtime_error("[!] Error : dynamic_cast Layer -> Linear");

        pW = pLinear->get_weight_ptr(); 
        in_dim = pW->get_row();
        out_dim = pW->get_col();
        grads.push_back(std::make_tuple(weight_name + std::to_string(i), Mat::zeros(in_dim, out_dim)));

        pb = pLinear->get_bias_ptr(); 
        in_dim = pb->get_row();
        out_dim = pb->get_col();
        grads.push_back(std::make_tuple(bias_name + std::to_string(i), Mat::zeros(in_dim, out_dim)));
    }
    */
    return;
}
