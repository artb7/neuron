#ifndef _MAT2D_H_
#define _MAT2D_H_

#include <assert.h>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <stdint.h>


class Mat2d {
public: 
    Mat2d();
	Mat2d(uint32_t row, uint32_t col, float* data);
	~Mat2d();
	Mat2d(const Mat2d& other);
	Mat2d& operator = (const Mat2d& other);

	uint32_t get_row();
	uint32_t get_col();

    //void operator << (const Mat2d& t);

	Mat2d operator - ();

	float& operator () (uint32_t row, uint32_t col);
	Mat2d operator [] (const Mat2d& other);

	Mat2d operator + (const Mat2d& other);
	Mat2d operator - (const Mat2d& other);
	Mat2d operator * (const Mat2d& other);
	Mat2d operator / (const Mat2d& other);
	Mat2d operator < (const Mat2d& other);
	Mat2d operator <= (const Mat2d& other);
	Mat2d operator > (const Mat2d& other);
	Mat2d operator >= (const Mat2d& other);
	Mat2d operator == (const Mat2d& other);
	Mat2d operator != (const Mat2d& other);

	Mat2d operator + (float num);
	Mat2d operator - (float num);
	Mat2d operator * (float num);
	Mat2d operator / (float num);
	Mat2d operator < (float num);
	Mat2d operator <= (float num);
	Mat2d operator > (float num);
	Mat2d operator >= (float num);
	Mat2d operator == (float num);
	Mat2d operator != (float num);

    Mat2d max();
    Mat2d sum(int axis=-1);

	Mat2d dot(const Mat2d& other);
    Mat2d T();

private:
	float* data;
	uint32_t row;
	uint32_t col;
};

Mat2d zeros(uint32_t row, uint32_t col);
Mat2d operator + (float num, Mat2d tensor);
Mat2d operator - (float num, Mat2d tensor);
Mat2d operator * (float num, Mat2d tensor);
Mat2d operator / (float num, Mat2d tensor);
Mat2d reverse_boolean(Mat2d tensor);
Mat2d exp(Mat2d tensor);
Mat2d log(Mat2d tensor);

#endif //_MAT2D_H_
