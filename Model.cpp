#include "Model.hpp"

Model::Model() {
}

Model::~Model() {
    for (int i = 0; i < module.size(); ++i) {
        if (module[i] != nullptr)
            delete module[i];
    }
}

Mat2d<float> Model::operator(Mat2d<float>& x) {
    Mat2d<float> out = x;
    for (int i = 0; i < module.size(); ++i) {
        out = module[i]->forward(out); 
    }
    return out;
}

void backward(Mat2d<float> out) {
    Mat2d<float> dout = Mat::ones(out.get_row(), out.get_col());
    for (int i = module.size() - 1; i >= 0; --i) {
        dout = module[i]->backward(dout);
    }
}

void Model::connect_with_optimizer(Optim& optim) {
    this->optim = &optim;
    for (int i = 0; i < module.size(); ++i) {
        if (module[i]->has_parameters()) {
            //TODO has_pa, get_pPa
            params.push_back(module[i]->get_pParams());
        }
    }
}

void Model::connect_with_criterion(Layer& criterion) {
    this->criterion = &criterion;

}

