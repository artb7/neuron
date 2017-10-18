#ifndef _TENSOR_H_
#define _TENSOR_H_

#include <assert.h>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <stdint.h>


class Tensor {
public: 
        Tensor();
	Tensor(uint32_t dim0, uint32_t dim1, float* data);
	~Tensor();
	Tensor(const Tensor& other);

	uint32_t get_dim0();
	uint32_t get_dim1();

        //void operator << (const Tensor& t);

	Tensor operator - ();

	float& operator()(uint32_t i, uint32_t j);

	Tensor operator[](const Tensor& other);

	Tensor operator+(const Tensor& other);
	Tensor operator-(const Tensor& other);
	Tensor operator*(const Tensor& other);
	Tensor operator/(const Tensor& other);
	Tensor operator+(float num);
	Tensor operator-(float num);
	Tensor operator*(float num);
	Tensor operator/(float num);
	Tensor operator<(const Tensor& other);
	Tensor operator<=(const Tensor& other);
	Tensor operator<=(float num);
	Tensor operator>(const Tensor& other);
	Tensor operator>=(const Tensor& other);

	Tensor& operator=(const Tensor& other);

	Tensor dot(const Tensor& other);
        Tensor max();
        Tensor sum(int axis=-1);
        Tensor T();

private:
	float* data;
	uint32_t dim0;
	uint32_t dim1;
};

Tensor zeros(uint32_t dim0, uint32_t dim1);
Tensor operator+(float num, Tensor tensor);
Tensor operator-(float num, Tensor tensor);
Tensor operator*(float num, Tensor tensor);
Tensor operator/(float num, Tensor tensor);
Tensor reverse_boolean(Tensor tensor);
Tensor exp(Tensor tensor);
Tensor log(Tensor tensor);

#endif // _TENSOR_H_
