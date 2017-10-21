#include <iostream>

#include "Mat2d.hpp"


int main() {

    // [Test] operator with Mat2d<float>
    uint32_t row = 2, col = 2;
    float a_data[row * col] = {1, 1, 1, 1};
    float b_data[row * col] = {1, 2, 3, 4};
    Mat2d<float> A(row, col, a_data);
    Mat2d<float> B(row, col, b_data);

    std::cout << "Mat2d<float> A: " << std::endl;
    A.print();
    std::cout << "Mat2d<float> B: " << std::endl;
    B.print();
    std::cout << "Mat2d<float> A + B: " << std::endl;
    (A + B).print();
    std::cout << "Mat2d<float> A - B: " << std::endl;
    (A - B).print();
    std::cout << "Mat2d<float> A * B: " << std::endl;
    (A * B).print();
    std::cout << "Mat2d<float> A / B: " << std::endl;
    (A / B).print();
    std::cout << "Mat2d<float> A > B: " << std::endl;
    (A > B).print();	
    std::cout << "Mat2d<float> A >= B: " << std::endl;
    (A >= B).print();	
    std::cout << "Mat2d<float> A < B: " << std::endl;
    (A < B).print();	
    std::cout << "Mat2d<float> A <= B: " << std::endl;
    (A <= B).print();	
    std::cout << "Mat2d<float> C <- B: " << std::endl;
    std::cout << "Mat2d<float> C: " << std::endl;
    Mat2d<float> C = B;
    C.print();	

    // [Test] operator with num 
    float num = 5;
    std::cout << "Mat2d<float> B: " << std::endl;
    B.print();
    std::cout << "Mat2d<float> B + 5: " << std::endl;
    (B + num).print();
    std::cout << "Mat2d<float> B - 5: " << std::endl;
    (B - num).print();
    std::cout << "Mat2d<float> B * 5: " << std::endl;
    (B * num).print();
    std::cout << "Mat2d<float> B / 5: " << std::endl;
    (B / num).print();

    // [Test] vector broadcast
    float onevec_data[2] = {1, 2};
    Mat2d<float> onevec(1, 2, onevec_data);

    std::cout << "Mat2d<float> A: " << std::endl;
    A.print();
    std::cout << "Mat2d<float> onevec: " << std::endl;
    onevec.print();
    std::cout << "Mat2d<float> A + onevec: " << std::endl;
    (A + onevec).print();
    std::cout << "Mat2d<float> A + onevec.T(): " << std::endl;
    (A + onevec.T()).print();

    // [Test] indexing reference
    std::cout << "Mat2d<float> A: " << std::endl;
    A.print();
    std::cout << "Mat2d<float> A(0,0) <- 0: " << std::endl;
    A(0,0) = 0;
    A.print();

    // [Test] sum 
    uint32_t dim0_t = 2, dim1_t = 4;
    float t_data_1[dim0_t * dim1_t] = {1,2,3,4,5,6,7,8};
    Mat2d<float> t1(dim0_t, dim1_t, t_data_1);

    std::cout << "Mat2d<float> t1: " << std::endl;
    t1.print();
    std::cout << "Mat2d<float> t1.sum(0): " << std::endl;
    (t1.sum(0)).print();
    std::cout << "Mat2d<float> t1.sum(1): " << std::endl;
    (t1.sum(1)).print();

    // [Test] transpose 
    std::cout << "Mat2d<float> t1: " << std::endl;
    t1.print();
    std::cout << "Mat2d<float> t1.T(): " << std::endl;
    (t1.T()).print();

    // [Test] dot operator 
    std::cout << "Mat2d<float> t1.dot(t1.T()): " << std::endl;
    (t1.dot(t1.T())).print();


    // TODO : other operator and function regard to Mat2d<float>  test

    return 0;
}
