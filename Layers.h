#pragma once


struct Result_backward {
    float* grad;
    int size;
};

class MulLayer {
public:
    MulLayer();
    ~MulLayer();

    float forward(float x, float y);
    Result_backward backward(float dout);

private:
    float x, y;
    struct Result_backward result_backward;
};


class AddLayer {
public:
    AddLayer();
    ~AddLayer();

    float forward(float x, float y);
    Result_backward backward(float dout);

private:
    float x, y;
    struct Result_backward result_backward;
};


class LeakyReLU {
publid:
    LeakyReLU();
    ~LeakyReLU();

    float forward(float x);
    Result_backward backward(float dout);

private:
    struct Result_backward result_backward;

}
