#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int num_inp = 4;
const int inp_dim = 2;
const int hid_dim = 2;
const int output_dim = 1;

void LeakyReLU(float* z, int num_dim) {
    for (int i = 0; i < num_dim; ++i) {
        z[i] = z[i] >= 0 ? z[i] : 0.2 * z[i];
    }
}

float criterion(float output, float target) {

    float diff = (output - target);
    return 0.5 * diff * diff;
}

void Linear(float* input, float** layer, int in_dim, int out_dim, 
            float bias, float* output) {

    memset(output, 0, sizeof(float) * out_dim);

    for (int i = 0; i < out_dim; ++i) {
        for (int j = 0; j < in_dim; ++j) {
            output[i] += layer[i][j] * input[j];
        }
        output[i] += bias;
    }
}

int main() {
    printf("hello world!\n");
    float lr = 0.1;
   
    float input[4][2] = {
        {0, 0}, {0, 1}, {1, 0}, {1, 1}
    };
    float target[4] = {
        0, 1, 1, 0
    };

    float ** layer_1 = (float**)malloc(sizeof(float*) * hid_dim);
    for (int i = 0; i < hid_dim; ++i)
        *(layer_1 + i) = (float*)malloc(sizeof(float*) * inp_dim);
    for (int i = 0; i < hid_dim; ++i)
        for (int j = 0 ; j < inp_dim; ++j)
            layer_1[i][j] = 0.5;

    float bias_1 = 0.5;

    float ** layer_2 = (float**)malloc(sizeof(float*) * output_dim);
    for (int i = 0; i < output_dim; ++i)
        *(layer_2 + i) = (float*)malloc(sizeof(float*) * hid_dim);
    for (int i = 0; i < output_dim; ++i)
        for (int j = 0 ; j < hid_dim; ++j)
            layer_2[i][j] = 0.5;
    float bias_2 = 0.5;

    float* output_1 = (float*)calloc(hid_dim, sizeof(float));
    float* output_2 = (float*)calloc(output_dim, sizeof(float));

    for (int epoch = 0; epoch < 100; ++epoch) {
        for (int i = 0; i < num_inp; ++i) {

            Linear(input[i], layer_1, inp_dim, hid_dim, bias_1, output_1);
            Linear(output_1, layer_2, hid_dim, output_dim, bias_2, output_2);
                    
            float output = output_2[0];
            float loss = criterion(output, target[i]);
            printf("lr: %f,  loss: %f\n", lr,  loss);
            return 0;
            
//            float dw = (output - target) * (output >= 0 ? 1 : 0.2) * input;
//            float db = (output - target) * (output >= 0 ? 1 : 0.2) * 1;
//
//            weight -= lr * dw;
//            bias -= lr * db;
//
//            printf("output : %f\n"
//                   "target : %f\n"
//                   "weight : %f\n"
//                   "bias : %f\n"
//                   "dw : %f\n"
//                   "db : %f\n"
//                   "loss : %f\n", output, target, weight, bias, dw, db, loss);
        }
    }

    for (int i = 0; i < hid_dim; ++i)
        free(layer_1 + i);
    free(layer_1);

    for (int i = 0; i < output_dim; ++i)
        free(layer_2 + i);
    free(layer_2);

    free(output_1);
    free(output_2);

    return 0;
}
