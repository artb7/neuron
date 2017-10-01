#ifndef MATRIX_H
#define MATRIX_H

#include <assert.h>
#include <stdint.h>
//#include <tuple>

class Matrix {
public:
    Matrix(uint32_t dim0, uint32_t dim1, float *data);
    ~Matrix();
    Matrix(const Matrix &other);

    float* get_data();
    
    Matrix operator+(Matrix &other);
    Matrix operator-(Matrix &other);
    Matrix operator*(Matrix &other);
    Matrix operator/(Matrix &other);
    Matrix operator>(Matrix &other);
    Matrix operator<(Matrix &other);
    Matrix operator>=(Matrix &other);
    Matrix operator<=(Matrix &other);
    Matrix operator==(Matrix &other);
    Matrix operator()(uint32_t i, uint32_t j);
     
private:
    float* data;
    uint32_t dim0;
    uint32_t dim1;
    //std::tuple shape;  
};

#endif // MATRIX_H
