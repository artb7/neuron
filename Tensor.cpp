#include "Tensor.h"

Tensor::Tensor() {
    this->dim0 = 0;
    this->dim1 = 0;
    this->data = nullptr;
}

Tensor::Tensor(uint32_t dim0, uint32_t dim1, float* data) {
    this->dim0 = dim0;
    this->dim1 = dim1;
    this->data = new float[dim0 * dim1];
    for (int i = 0; i < (int)dim0; ++i) {
            for (int j = 0; j < (int)dim1; ++j) {
                    this->data[i * dim0 + j] = data[i * dim0 + j];
            }
    }
}

Tensor::~Tensor() {
    if (data != nullptr)
        delete data;
}

Tensor::Tensor(const Tensor& other) {
	this->dim0 = other.dim0;
	this->dim1 = other.dim1;
	this->data = new float[dim0 * dim1];
	for (int i = 0; i < (int)dim0; ++i) {
		for (int j = 0; j < (int)dim1; ++j) {
			this->data[i * dim0 + j] = other.data[i * dim0 + j];
		}
	}
}

uint32_t Tensor::get_dim0() { 
	return this->dim0;
}
uint32_t Tensor::get_dim1() {
	return this->dim1;
}

float Tensor::operator()(uint32_t i, uint32_t j) {
	assert (i < this->dim0 && j < this->dim1);
	return data[i * this->dim0 + j];	
}

Tensor Tensor::operator[](const Tensor& other) {
	assert (dim0 == other.dim0 && dim1 == other.dim1);
	float result_data[dim0 * dim1] = {0,};
	for (int i = 0; i < (int)dim0; ++i) {
		for (int j = 0; j < (int)dim1; ++j) {
			int index = i * dim0 + j;
			if (other.data[index] == 1)
				result_data[index] = data[index];
			else
				result_data[index] = 0;
		}
	}
	return Tensor(dim0, dim1, result_data);
}

Tensor Tensor::operator+(const Tensor& other) {
	assert (dim0 == other.dim0 && dim1 == other.dim1);
	float result_data[dim0 * dim1] = {0,};
	//float* result_data = new float[dim0 * dim1];
	for (int i = 0; i < (int)dim0; ++i) {
		for (int j = 0; j < (int)dim1; ++j) {
			result_data[i * dim0 + j] =\
				data[i * dim0 + j] +\
				other.data[i * dim0 + j];
		}
	}
	return Tensor(dim0, dim1, result_data);
}

Tensor Tensor::operator-(const Tensor& other) {
	assert (dim0 == other.dim0 && dim1 == other.dim1);
	float result_data[dim0 * dim1] = {0,};
	//float* result_data = new float[dim0 * dim1];
	for (int i = 0; i < (int)dim0; ++i) {
		for (int j = 0; j < (int)dim1; ++j) {
			result_data[i * dim0 + j] =\
				data[i * dim0 + j] -\
				other.data[i * dim0 + j];
		}
	}
	return Tensor(dim0, dim1, result_data);
}

Tensor Tensor::operator*(const Tensor& other) {
	assert (dim0 == other.dim0 && dim1 == other.dim1);
	float result_data[dim0 * dim1] = {0,};
	//float* result_data = new float[dim0 * dim1];
	for (int i = 0; i < (int)dim0; ++i) {
		for (int j = 0; j < (int)dim1; ++j) {
			result_data[i * dim0 + j] =\
				data[i * dim0 + j] *\
				other.data[i * dim0 + j];
		}
	}
	return Tensor(dim0, dim1, result_data);
}

Tensor Tensor::operator/(const Tensor& other) {
	assert (dim0 == other.dim0 && dim1 == other.dim1);
	for (int i = 0; i < (int)dim0; ++i) {
		for(int j = 0; j < (int)dim1; ++j) {
			if (other.data[i * dim0 + j] == 0) { 
				throw "Zero division Error";
			}
		}
	}
	float result_data[dim0 * dim1] = {0,};
	//float* result_data = new float[dim0 * dim1];
	for (int i = 0; i < (int)dim0; ++i) {
		for (int j = 0; j < (int)dim1; ++j) {
			result_data[i * dim0 + j] =\
				data[i * dim0 + j] /\
				other.data[i * dim0 + j];
		}
	}
	return Tensor(dim0, dim1, result_data);
}


Tensor Tensor::operator<(const Tensor& other) {	
	assert (dim0 == other.dim0 && dim1 == other.dim1);
	float result_data[dim0 * dim1] = {0,};
	//float* result_data = new float[dim0 * dim1];
	for (int i = 0; i < (int)dim0; ++i) {
		for (int j = 0; j < (int)dim1; ++j) {
			int index = i * dim0 + j;
			result_data[index] =\
				(data[index] < other.data[index]) ?\
				1.0 : 0.0;
		}
	}
	return Tensor(dim0, dim1, result_data);
}
Tensor Tensor::operator<=(const Tensor& other) {
	assert (dim0 == other.dim0 && dim1 == other.dim1);
	float result_data[dim0 * dim1] = {0,};
	//float* result_data = new float[dim0 * dim1];
	for (int i = 0; i < (int)dim0; ++i) {
		for (int j = 0; j < (int)dim1; ++j) {
			int index = i * dim0 + j;
			result_data[index] =\
				(data[index] <= other.data[index]) ?\
				1.0 : 0.0;
		}
	}
	return Tensor(dim0, dim1, result_data);
}
Tensor Tensor::operator>(const Tensor& other) {
	assert (dim0 == other.dim0 && dim1 == other.dim1);
	float result_data[dim0 * dim1] = {0,};
	//float* result_data = new float[dim0 * dim1];
	for (int i = 0; i < (int)dim0; ++i) {
		for (int j = 0; j < (int)dim1; ++j) {
			int index = i * dim0 + j;
			result_data[index] =\
				(data[index] > other.data[index]) ?\
				1.0 : 0.0;
		}
	}
	return Tensor(dim0, dim1, result_data);
}
Tensor Tensor::operator>=(const Tensor& other) {
	assert (dim0 == other.dim0 && dim1 == other.dim1);
	float result_data[dim0 * dim1] = {0,};
	//float* result_data = new float[dim0 * dim1];
	for (int i = 0; i < (int)dim0; ++i) {
		for (int j = 0; j < (int)dim1; ++j) {
			int index = i * dim0 + j;
			result_data[index] =\
				(data[index] >= other.data[index]) ?\
				1.0 : 0.0;
		}
	}
	return Tensor(dim0, dim1, result_data);
}

Tensor& Tensor::operator=(const Tensor& other) {
	assert (dim0 == other.dim0 && dim1 == other.dim1);
	for (int i = 0; i < (int)dim0; ++i) {
		for (int j = 0; j < (int)dim1; ++j) {
			int index = i * dim0 + j;
			data[index] = other.data[index];
		}
	}
	return *this;
}


Tensor Tensor::matmul(const Tensor& other) {
	float result_data[dim0 * other.dim1] = {0,}; 
	for (int i = 0; i < (int)dim0; ++i) {
		for (int j = 0; j < (int)other.dim1; ++j) {
			for (int k = 0; k < (int)dim1; ++k) {
				result_data[i * dim0 + j] +=\
					data[i * dim0 + k] *\
					other.data[j + other.dim1 * k];
					
			}
		}
	}
	return Tensor(dim0, other.dim1, result_data);
}
