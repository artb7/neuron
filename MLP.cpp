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
    
    zero_grad();    
}

MLP::~MLP() {
    //TODO release resource
}

auto MLP::predict(Mat2d<float> x) {
    Mat2d<float> out = x;
    for (int i = 0; i < (int)module.size(); ++i) {
        out = module[i]->forward(out);
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
    Mat2d<float> dout = Mat::ones(t.get_row(), this->out_dim);

    for (int i = module.size() - 1; i >= 0; --i) {
        dout = module[i]->backward(dout);
    }
    
}

void MLP::zero_grad() {

    Mat2d* W; 
    Mat2d* b;
    std::string weight_name = "W";
    std::string bias_name = "b";
    for (int i = 0; i < module.size(); ++i) {
        W = module[i]->get_weight_ptr(); 
        uint32_t in_dim = W->get_row();
        uint32_t out_dim = W->get_col();
        grads.push_back(std::make_tuple(weight_name + string(i), Mat::zeros(in_dim, out_dim)));
        b = module[i]->get_bias_ptr(); 
        in_dim = b->get_row();
        out_dim = b->get_col();
        grads.push_back(std::make_tuple(bias_name + string(i), Mat::zeros(in_dim, out_dim)));

    }
}
