#include "Matrix.h"

Matrix::Matrix(uint32_t dim0, uint32_t dim1, float *data) {
    this->dim0 = dim0;
    this->dim1 = dim1;
    this->data = new float [dim0 * dim1];
    for (int i = 0; i < dim0; ++i) {
        for (int j = 0; j < dim1; ++j) {
            this->data[i * dim0 + j] = data[i * dim0 + j];
        }
    }
}
Matrix::~Matrix() {
    delete this->data;
}
Matrix::Matrix(const Matrix &other) {
    this->data = new float[other.dim0 * other.dim1];
    this->dim0 = other.dim0;
    this->dim1 = other.dim1;
    for (int i = 0; i < dim0; ++i) {
        for (int j = 0; j < dim1; ++j) {
            this->data[i * dim0 + j] = other.data[i * dim0 + j];
        }
    }
}
float* Matrix::get_data() {
    return this->data;
}

Matrix Matrix::operator+(Matrix &other) {

    assert (this->dim0 == other.dim0 && this->dim1 == other.dim1);

    float* result_data = new float[this->dim0 * this->dim1]; 
    for (int i = 0; i < this->dim0; ++i) {
        for (int j = 0; j < this->dim1; ++j) {
            result_data[i * this->dim0 + j] =\
                        this->data[i * this->dim0 + j] +\
                        other.data[i * this->dim0 + j];
        }
    }

    /*
    float** result_data = new float*[this->dim0]; 
    for (int i = 0; i < this->dim0; ++i) {
        result_data = new float[this->dim1];
    }
    for (int i = 0; i < this->dim0; ++i) {
        for (int j = 0; j < this->dim1; ++j) {
            result_data[i][j] = this->data[i * this->dim0 + j] + other.data[i * this->dim0 + j];
        }
    }
    */
    return Matrix(this->dim0, this->dim1, result_data);
}
Matrix Matrix::operator-(Matrix &other){};
Matrix Matrix::operator*(Matrix &other){};
Matrix Matrix::operator/(Matrix &other){};
Matrix Matrix::operator>(Matrix &other){};
Matrix Matrix::operator<(Matrix &other){};
Matrix Matrix::operator>=(Matrix &other){};
Matrix Matrix::operator<=(Matrix &other){};
Matrix Matrix::operator==(Matrix &other){};
Matrix Matrix::operator()(uint32_t i, uint32_t j){};
