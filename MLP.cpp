#include "MLP.hpp"

MLP::MLP(uint32_t in_dim, uint32_t hidden_dim, uint32_t out_dim) {
    this->in_dim = in_dim;
    this->hidden_dim = hidden_dim;
    this->out_dim = out_dim;
    Layer *layer0 = new Linear(in_dim, hidden_dim);
    Layer *layer1 = new Linear(hidden_dim, out_dim);
    Layer *l_relu = new LeakyReLU();
    auto layer = std::make_tuple("linear0", layer0);
    module.push_back(layer);
    layer = std::make_tuple("l_relu", l_relu);
    module.push_back(layer);
    layer = std::make_tuple("linear1", layer1);
    module.push_back(layer);

    Linear* pLinear = dynamic_cast<Linear*>(layer0);
    if (!pLinear) 
        throw std::runtime_error("[!] Error : dynamic_cast Layer -> Linear");
    auto param = std::make_tuple("W0", pLinear->get_pWeight());
    params.push_back(param);
    param = std::make_tuple("b0", pLinear->get_pBias());
    params.push_back(param);
    pLinear = dynamic_cast<Linear*>(layer1);
    if (!pLinear) 
        throw std::runtime_error("[!] Error : dynamic_cast Layer -> Linear");
    param = std::make_tuple("W1", pLinear->get_pWeight());
    params.push_back(param);
    param = std::make_tuple("b1", pLinear->get_pBias());
    params.push_back(param);
    
    auto grad = std::make_tuple("W0", Mat::zeros(in_dim, hidden_dim));
    grads.push_back(grad);
    grad = std::make_tuple("b0", Mat::zeros(1, hidden_dim));
    grads.push_back(grad);
    grad = std::make_tuple("W1", Mat::zeros(hidden_dim, out_dim));
    grads.push_back(grad);
    grad = std::make_tuple("b1", Mat::zeros(1, out_dim));
    grads.push_back(grad);

    grad = std::make_tuple("W0", Mat::zeros(in_dim, hidden_dim));
    numerical_grads.push_back(grad);
    grad = std::make_tuple("b0", Mat::zeros(1, hidden_dim));
    numerical_grads.push_back(grad);
    grad = std::make_tuple("W1", Mat::zeros(hidden_dim, out_dim));
    numerical_grads.push_back(grad);
    grad = std::make_tuple("b1", Mat::zeros(1, out_dim));
    numerical_grads.push_back(grad);
}

MLP::~MLP() {
    for (int i = 0; i < (int)module.size(); ++i) {
        delete std::get<1>(module[i]);
    }
}

Mat2d<float> MLP::predict(Mat2d<float>& x) {
    Mat2d<float> out = x;
    for (int i = 0; i < (int)module.size(); ++i) {
        out = std::get<1>(module[i])->forward(out);
    }
    return out;
}

Mat2d<float> MLP::loss(Mat2d<float>& x, Mat2d<float>& t) {
    Mat2d<float> out = predict(x);
    return criterion.compute(out, t); 
}


std::vector<std::tuple<std::string, Mat2d<float>>> MLP::numerical_gradient(Mat2d<float>& x, Mat2d<float>& t) {

    for (int i = 0; i < (int)numerical_grads.size(); ++i) {
        std::get<1>(numerical_grads[i]) = numerical_gradient(std::get<0>(params[i]), x, t); 
    }
    return numerical_grads;
}


Mat2d<float> MLP::numerical_gradient(std::string name, Mat2d<float>& x, Mat2d<float>& t) {
    float h = 1e-4;

    Mat2d<float>* pParam;
    for (int i = 0; i < (int)params.size(); ++i) {
        if (std::get<0>(params[i]) == name)
            pParam = std::get<1>(params[i]);
    }
    Mat2d<float> grad = Mat::zeros(pParam->get_row(), pParam->get_col());

    Mat2d<float> fxh1;
    Mat2d<float> fxh2;
    for (int i = 0; i < (int)pParam->get_row(); ++i) {
        for (int j = 0; j < (int)pParam->get_col(); ++j) {
            (*pParam)(i, j) += h;
            fxh1 = loss(x, t);
            (*pParam)(i, j) -= 2 * h;
            fxh2 = loss(x, t);
            grad(i, j) = (fxh1(0, 0) - fxh2(0, 0)) / (2 * h);

            (*pParam)(i, j) += h;
        }
    }
    return grad;
}


std::vector<std::tuple<std::string, Mat2d<float>>> MLP::gradient(Mat2d<float>& x, Mat2d<float>& t){
    loss(x, t);
    Mat2d<float> dout = Mat::ones(t.get_row(), this->out_dim);

    dout = criterion.backward(dout);
    for (int i = (int)module.size() - 1; i >= 0; --i) {
        dout = std::get<1>(module[i])->backward(dout);
    }

    Linear* pLinear = dynamic_cast<Linear*>(std::get<1>(module[0]));
    if (!pLinear) 
        throw std::runtime_error("[!] Error : dynamic_cast Layer -> Linear");
    std::get<1>(grads[0]) = pLinear->get_dW();
    std::get<1>(grads[1]) = pLinear->get_db();
    pLinear = dynamic_cast<Linear*>(std::get<1>(module[2]));
    if (!pLinear) 
        throw std::runtime_error("[!] Error : dynamic_cast Layer -> Linear");
    std::get<1>(grads[2]) = pLinear->get_dW();
    std::get<1>(grads[3]) = pLinear->get_db();
    
    return grads;    
}

std::vector<std::tuple<std::string, Mat2d<float>*>> MLP::get_params() {
    return params;
}

void MLP::zero_grad() {
    
    //TODO use iterator ?
    for (int i = 0; i < (int)grads.size(); ++i) {
        std::get<1>(grads[i]).fill_zeros();
    }

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

void MLP::update_params(float lr) {
      
    Mat2d<float>* pParam;
    Mat2d<float> grad;
    for (int i = 0; i < (int)params.size(); ++i) {
        pParam = std::get<1>(params[i]);
        grad = std::get<1>(grads[i]);
        *pParam = *pParam - (lr * grad);
    }
    return;
}
