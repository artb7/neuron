#include <iostream>
#include <string>
#include <tuple>

#include "MLP.hpp"

int main() {
    using std::cout;
    using std::endl;

    float x_data[4 * 2] = {0, 0, 0, 1, 1, 0, 1, 1}; 
    float y_data[4 * 1] = {0, 1, 1, 0};
    auto X = Mat2d<float>(4, 2, x_data);
    auto Y = Mat2d<float>(4, 1, y_data);
    
    float alpha = 1e-2; 
    
    auto in_dim = 2;
    auto hidden_dim = 5;
    auto out_dim = 2;
    MLP model = MLP(in_dim, hidden_dim, out_dim);
    
    auto output = model.predict(X);
    auto loss = model.loss(X, Y); 
    std::cout << "output : " << std::endl;
    output.print();
    std::cout << "loss: " << std::endl;
    loss.print();

    auto gradient = model.gradient(X, Y);
    std::cout << "gradient : " << std::endl;

    std::string name;
    Mat2d<float> grad;
    for (int i = 0; i < (int)gradient.size(); ++i) {
        // Why not working?
        //auto [name, grad] = gradient[i];
        std::tie(name, grad) = gradient[i];
        cout << name << endl;
        grad.print();
    }
    cout << endl;

    auto numerical_gradient = model.numerical_gradient(X, Y);
    cout << "numerical_gradient : " << endl;

    for (int i = 0; i < (int)numerical_gradient.size(); ++i) {
        // Why not working?
        //auto [name, grad] = gradient[i];
        std::tie(name, grad) = numerical_gradient[i];
        cout << name << endl;
        grad.print();
    }
    cout << endl;

    cout << "diff gradient and numerical_gradient : " << endl;

    Mat2d<float> grad1;
    Mat2d<float> grad2;
    for (int i = 0; i < (int)numerical_gradient.size(); ++i) {
        // Why not working?
        //auto [name, grad] = gradient[i];
        std::tie(name, grad1) = gradient[i];
        std::tie(name, grad2) = numerical_gradient[i];
        
        cout << name << endl;
        (grad1 - grad2).print();
    }
    cout << endl;
    /*
    auto params = model.get_params();
    std::cout << "before update param: " << std::endl;
    Mat2d<float>* param;
    for (int i = 0; i < (int)params.size(); ++i) {
        // Why not working?
        //auto [name, grad] = gradient[i];
        std::tie(name, param) = params[i];
        cout << name << endl;
        param->print();
    }

    model.update_params(alpha);

    cout << endl;
    params = model.get_params();
    std::cout << "after update param: " << std::endl;
    for (int i = 0; i < (int)params.size(); ++i) {
        // Why not working?
        //auto [name, grad] = gradient[i];
        std::tie(name, param) = params[i];
        cout << name << endl;
        param->print();
    }

    model.zero_grad();
    */

    /*
    Mat2d<float> output;
    Mat2d<float> loss;
    for (int step = 0; step < 10000; ++step) {
        output = model.predict(X);
        loss = model.loss(X, Y); 
        
        if (step % 200 == 0) {
            cout << endl;
            cout << "step : " << step << endl;
            cout << "loss : " << endl;
            loss.print();
            cout << "output : " << endl;
            output.print();
            cout << endl;
        }
        
        model.gradient(X, Y);
        model.update_params(alpha);
        model.zero_grad();
    }
    */
    
    return 0;
};
