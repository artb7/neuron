#include <iostream>

#include "Matrix.h"

void print(Matrix m) {
    float *data = m.get_data();
    for(int i = 0; i < 2; ++i) {
       for(int j = 0; j < 2; ++j) {
           std::cout << data[i * 2 + j] << " ";
       }
       std::cout << std::endl;
    }
    return;
}

int main() {
    uint32_t cols = 2, rows = 2;
    float a_data[4] = {1, 1, 1, 1};
    float b_data[4] = {1, 2, 3, 4};

    Matrix A = Matrix(cols, rows, a_data);
    Matrix B = Matrix(cols, rows, b_data);
    Matrix C = A;
    std::cout << "hello " << std::endl;
    print(A);
    print(C);
    print(A+B);

    return 0;
}
