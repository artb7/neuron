#include "test_mat2d.hpp"

uint32_t row = 2, col = 2;
float a_data[row * col] = {1, 1, 0, 0};
float b_data[row * col] = {1, 2, 3, 4};
Mat2d<float> A(row, col, a_data);
Mat2d<float> B(row, col, b_data);

void test_arithmetic_operator_with_Mat() {

    std::cout << "Mat2d<float> A: " << std::endl;
    A.print();
    std::cout << "Mat2d<float> B: " << std::endl;
    B.print();
    std::cout << "Mat2d<float> -A: " << std::endl;
    (-A).print();
    std::cout << "Mat2d<float> !A: " << std::endl;
    (!A).print();
    std::cout << "Mat2d<float> B[A]: " << std::endl;
    (B[A]).print();
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
}

void test_arithmetic_operator_with_num() {
    // [Test] operator with num 
    float num = 5;
    std::cout << "B: " << std::endl;
    B.print();
    std::cout << "(B + 5): " << std::endl;
    (B + num).print();
    std::cout << "(B - 5): " << std::endl;
    (B - num).print();
    std::cout << "(B * 5): " << std::endl;
    (B * num).print();
    std::cout << "(B / 5): " << std::endl;
    (B / num).print();

    std::cout << "B: " << std::endl;
    B.print();
    std::cout << "(1 + B) : " << std::endl;
    (1 + B).print();
    std::cout << "(1 - B) : " << std::endl;
    (1 - B).print();
    std::cout << "(4 * B) : " << std::endl;
    (4 * B).print();
    std::cout << "(4 / B) : " << std::endl;
    (4 / B).print();
}

void test_vector_broadcast() {

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
}

void test_indexing_reference() {
    // [Test] indexing reference
    std::cout << "Mat2d<float> A: " << std::endl;
    A.print();
    std::cout << "Mat2d<float> A(0,0) <- 0: " << std::endl;
    A(0,0) = 0;
    A.print();
}

void test_sum() {
    uint32_t dim0_t = 2, dim1_t = 4;
    float t_data_1[dim0_t * dim1_t] = {1,2,3,4,5,6,7,8};
    Mat2d<float> t1(dim0_t, dim1_t, t_data_1);

    std::cout << "Mat2d<float> t1: " << std::endl;
    t1.print();
    std::cout << "Mat2d<float> t1.sum(0): " << std::endl;
    (t1.sum(0)).print();
    std::cout << "Mat2d<float> t1.sum(1): " << std::endl;
    (t1.sum(1)).print();
}

void test_max() {
    uint32_t dim0_t = 2, dim1_t = 4;
    float t_data_1[dim0_t * dim1_t] = {1,2,3,4,5,6,7,8};
    Mat2d<float> t1(dim0_t, dim1_t, t_data_1);
    std::cout << "Mat2d<float> t1: " << std::endl;
    t1.print();
    std::cout << "Mat2d<float> t1.max(): " << std::endl;
    (t1.max()).print();
    std::cout << "Mat2d<float> t1.max(0): " << std::endl;
    (t1.max(0)).print();
    std::cout << "Mat2d<float> t1.max(1): " << std::endl;
    (t1.max(1)).print();
}

void test_dot_operator() {

    uint32_t dim0_t = 2, dim1_t = 4;
    float t_data_1[dim0_t * dim1_t] = {1,2,3,4,5,6,7,8};
    Mat2d<float> t1(dim0_t, dim1_t, t_data_1);
    std::cout << "Mat2d<float> t1: " << std::endl;
    t1.print();
    std::cout << "Mat2d<float> t1.dot(t1.T()): " << std::endl;
    (t1.dot(t1.T())).print();
}

void test_transpose() {
    uint32_t dim0_t = 2, dim1_t = 4;
    float t_data_1[dim0_t * dim1_t] = {1,2,3,4,5,6,7,8};
    Mat2d<float> t1(dim0_t, dim1_t, t_data_1);
    std::cout << "Mat2d<float> t1: " << std::endl;
    t1.print();
    std::cout << "Mat2d<float> t1.T(): " << std::endl;
    (t1.T()).print();
}

void test_misc() {

    std::cout << "Mat::zeros(2, 2) : " << std::endl;
    (Mat::zeros(2, 2)).print();

    std::cout << "1 + Mat::ones(2, 2) : " << std::endl;
    (1 + Mat::ones(2, 2)).print();

    std::cout << "Mat<float> B : " << std::endl;
    B.print();
   
    std::cout << "Mat::exp(B) : " << std::endl;
    (Mat::exp(B)).print();

    std::cout << "Mat::log(B) : " << std::endl;
    (Mat::log(B)).print();
}
