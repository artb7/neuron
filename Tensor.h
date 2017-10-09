#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <stdint.h>
#include <assert.h>

class Tensor{
public: 
	Tensor(uint32_t dim0, uint32_t dim1, float* data);
	~Tensor();
	Tensor(const Tensor& other);

	uint32_t get_dim0();
	uint32_t get_dim1();

	float operator()(uint32_t i, uint32_t j);

	Tensor operator[](const Tensor& other);

	Tensor operator+(const Tensor& other);
	Tensor operator-(const Tensor& other);
	Tensor operator*(const Tensor& other);
	Tensor operator/(const Tensor& other);
	Tensor operator<(const Tensor& other);
	Tensor operator<=(const Tensor& other);
	Tensor operator>(const Tensor& other);
	Tensor operator>=(const Tensor& other);

	Tensor& operator=(const Tensor& other);

	Tensor matmul(const Tensor& other);

private:
	float* data;
	uint32_t dim0;
	uint32_t dim1;
};
#endif // _MATRIX_H_
