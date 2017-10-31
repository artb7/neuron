#include "test_layers"
#include "test_mat2d"
#include "test_mlp"

int main() {
    test_LeakyReLU();
    test_Sigmoid();
    test_Linear();
    test_SoftmaxWithLoss();
    return 0;
}
