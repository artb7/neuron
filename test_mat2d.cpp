#include <iostream>

#include "Mat2d.hpp"
#include "Layers.hpp"

void print(Mat2d t) {
    uint32_t dim0 = t.get_row();
    uint32_t dim1 = t.get_col();
    for (int i = 0; i < (int)dim0; ++i) {
        for (int j = 0; j < (int)dim1; ++j) {
            std::cout << t(i, j) << " ";	
        }
        std::cout << std::endl;
    }
    return;
}

int main() {

    // [Test] operator with Mat2d
    uint32_t row = 2, col = 2;
    float a_data[row * col] = {1, 1, 1, 1};
    float b_data[row * col] = {1, 2, 3, 4};
    Mat2d A(row, col, a_data);
    Mat2d B(row, col, b_data);

    std::cout << "Mat2d A: " << std::endl;
    print(A);
    std::cout << "Mat2d B: " << std::endl;
    print(B);
    std::cout << "Mat2d A + B: " << std::endl;
    print(A + B);
    std::cout << "Mat2d A - B: " << std::endl;
    print(A - B);
    std::cout << "Mat2d A * B: " << std::endl;
    print(A * B);
    std::cout << "Mat2d A / B: " << std::endl;
    print(A / B);
    std::cout << "Mat2d A > B: " << std::endl;
    print(A > B);	
    std::cout << "Mat2d A >= B: " << std::endl;
    print(A >= B);	
    std::cout << "Mat2d A < B: " << std::endl;
    print(A < B);	
    std::cout << "Mat2d A <= B: " << std::endl;
    print(A <= B);	
    std::cout << "Mat2d C <- B: " << std::endl;
    std::cout << "Mat2d C: " << std::endl;
    Mat2d C = B;
    print(C);	

    // [Test] operator with num 
    float num = 5;
    std::cout << "Mat2d B: " << std::endl;
    print(B);
    std::cout << "Mat2d B + 5: " << std::endl;
    print(B + num);
    std::cout << "Mat2d B - 5: " << std::endl;
    print(B - num);
    std::cout << "Mat2d B * 5: " << std::endl;
    print(B * num);
    std::cout << "Mat2d B / 5: " << std::endl;
    print(B / num);

    // [Test] vector broadcast
    float onevec_data[2] = {1, 2};
    Mat2d onevec(1, 2, onevec_data);

    std::cout << "Mat2d A: " << std::endl;
    print(A);
    std::cout << "Mat2d onevec: " << std::endl;
    print(onevec);
    std::cout << "Mat2d A + onevec: " << std::endl;
    print(A + onevec);
    std::cout << "Mat2d A + onevec.T(): " << std::endl;
    print(A + onevec.T());

    // [Test] indexing reference
    std::cout << "Mat2d A: " << std::endl;
    print(A);
    std::cout << "Mat2d A(0,0) <- 0: " << std::endl;
    A(0,0) = 0;
    print(A);

    // [Test] sum 
    uint32_t dim0_t = 2, dim1_t = 4;
    float t_data_1[dim0_t * dim1_t] = {1,2,3,4,5,6,7,8};
    Mat2d t1(dim0_t, dim1_t, t_data_1);

    std::cout << "Mat2d t1: " << std::endl;
    print(t1);
    std::cout << "Mat2d t1.sum(0): " << std::endl;
    print(t1.sum(0));
    std::cout << "Mat2d t1.sum(1): " << std::endl;
    print(t1.sum(1));

    // [Test] transpose 
    std::cout << "Mat2d t1: " << std::endl;
    print(t1);
    std::cout << "Mat2d t1.T(): " << std::endl;
    print(t1.T());

    // [Test] dot operator 
    std::cout << "Mat2d t1.dot(t1.T()): " << std::endl;
    print(t1.dot(t1.T()));


    // TODO : other operator and function regard to Mat2d  test

    return 0;
}
