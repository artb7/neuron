#include "Tensor.hpp"

Tensor::Tensor() {
    this->dim0 = 0;
    this->dim1 = 0;
    this->data = nullptr;
}

Tensor::Tensor(uint32_t dim0, uint32_t dim1, float* data) {
    //std::cout << "hello" << std::endl;
    this->dim0 = dim0;
    this->dim1 = dim1;
    this->data = new float[dim0 * dim1];
    for (int i = 0; i < (int)dim0; ++i) {
        for (int j = 0; j < (int)dim1; ++j) {
            int index = (int)dim1 * i + j;
            this->data[index] = data[index];
            //std::cout << index << " :";
            //std::cout << data[index] << " ";
        }
        //std::cout << std::endl;
    }
}

Tensor::~Tensor() {
    if (data != nullptr)
        delete data;
}

Tensor::Tensor(const Tensor& other) {
    //std::cout << "hello" << std::endl;
    this->dim0 = other.dim0;
    this->dim1 = other.dim1;
    this->data = new float[dim0 * dim1];
    for (int i = 0; i < (int)dim0; ++i) {
        for (int j = 0; j < (int)dim1; ++j) {
            int index = (int)dim1 * i + j;
            this->data[index] = other.data[index];
        }
    }
}

uint32_t Tensor::get_dim0() { 
    return this->dim0;
}
uint32_t Tensor::get_dim1() {
    return this->dim1;
}


Tensor Tensor::operator-() {
    float result_data[dim0 * dim1] = {0,};
    for (int i = 0; i < (int)dim0; ++i) {
        for (int j = 0; j < (int)dim1; ++j) {
            int index = i * dim1 + j;
            result_data[index] = -data[index];
        }
    }
    return Tensor(dim0, dim1, result_data);
}

float& Tensor::operator()(uint32_t i, uint32_t j) {
    assert (i < this->dim0 && j < this->dim1);
    return data[i * this->dim1 + j];	
}

Tensor Tensor::operator[](const Tensor& other) {
    assert (dim0 == other.dim0 && dim1 == other.dim1);
	float result_data[dim0 * dim1] = {0,};
        // TODO 1 -> true
	for (int i = 0; i < (int)dim0; ++i) {
		for (int j = 0; j < (int)dim1; ++j) {
			int index = i * dim1 + j;
			if (other.data[index] == 1)
				result_data[index] = data[index];
			else
				result_data[index] = 0;
		}
	}
        // TODO return tensor is not self.
        // how to implement numpy indexing
	return Tensor(dim0, dim1, result_data);
}

Tensor Tensor::operator+(const Tensor& other) {
    assert ((dim0 == other.dim0 && dim1 == other.dim1) or\
            (dim0 == other.dim0 && other.dim1 == 1) or\
            (dim1 == other.dim1 && other.dim0 == 1));
    float result_data[dim0 * dim1] = {0,};
    if (dim0 == other.dim0 && other.dim1 == 1) {
        for (int i = 0; i < (int)dim0; ++i) {
            for (int j = 0; j < (int)dim1; ++j) {
                int index = dim1 * i + j;
                result_data[index] = data[index] + other.data[i];
            }
        }
    }
    else if (dim1 == other.dim1 && other.dim0 == 1) {
        for (int i = 0; i < (int)dim0; ++i) {
            for (int j = 0; j < (int)dim1; ++j) {
                int index = dim1 * i + j;
                result_data[index] = data[index] + other.data[j];
            }
        }
    }
    else {
        for (int i = 0; i < (int)dim0; ++i) {
            for (int j = 0; j < (int)dim1; ++j) {
                int index = dim1 * i + j;
                result_data[index] = data[index] + other.data[index];
            }
        }
    }
    return Tensor(dim0, dim1, result_data);
}


Tensor Tensor::operator-(const Tensor& other) {
    assert ((dim0 == other.dim0 && dim1 == other.dim1) or\
            (dim0 == other.dim0 && other.dim1 == 1) or\
            (dim1 == other.dim1 && other.dim0 == 1));
    float result_data[dim0 * dim1] = {0,};
    if (dim0 == other.dim0 && other.dim1 == 1) {
        for (int i = 0; i < (int)dim0; ++i) {
            for (int j = 0; j < (int)dim1; ++j) {
                int index = dim1 * i + j;
                result_data[index] = data[index] - other.data[i];
            }
        }
    }
    else if (dim1 == other.dim1 && other.dim0 == 1) {
        for (int i = 0; i < (int)dim0; ++i) {
            for (int j = 0; j < (int)dim1; ++j) {
                int index = dim1 * i + j;
                result_data[index] = data[index] - other.data[j];
            }
        }
    }
    else {
        for (int i = 0; i < (int)dim0; ++i) {
            for (int j = 0; j < (int)dim1; ++j) {
                int index = dim1 * i + j;
                result_data[index] = data[index] - other.data[index];
            }
        }
    }
    return Tensor(dim0, dim1, result_data);
}


Tensor Tensor::operator*(const Tensor& other) {
    assert ((dim0 == other.dim0 && dim1 == other.dim1) or\
            (dim0 == other.dim0 && other.dim1 == 1) or\
            (dim1 == other.dim1 && other.dim0 == 1));
    float result_data[dim0 * dim1] = {0,};
    //float* result_data = new float[dim0 * dim1];
    for (int i = 0; i < (int)dim0; ++i) {
        for (int j = 0; j < (int)dim1; ++j) {
            int index = dim1 * i + j;
            result_data[index] = data[index] * other.data[index];
        }
    }
    return Tensor(dim0, dim1, result_data);
}


Tensor Tensor::operator/(const Tensor& other) {
    assert ((dim0 == other.dim0 && dim1 == other.dim1) or\
            (dim0 == other.dim0 && other.dim1 == 1) or\
            (dim1 == other.dim1 && other.dim0 == 1));
    for (int i = 0; i < (int)dim0; ++i) {
        for(int j = 0; j < (int)dim1; ++j) {
            if (other.data[i * dim1 + j] == 0) { 
                throw "Zero division Error";
            }
        }
    }

    float result_data[dim0 * dim1] = {0,};
    //float* result_data = new float[dim0 * dim1];
    for (int i = 0; i < (int)dim0; ++i) {
        for (int j = 0; j < (int)dim1; ++j) {
            int index = dim1 * i + j;
            result_data[index] = data[index] / other.data[index];
        }
    }
    return Tensor(dim0, dim1, result_data);
}


Tensor Tensor::operator+(float num) {

    float result_data[dim0 * dim1] = {0,};
    for (int i = 0; i < (int)dim0; ++i) {
        for (int j = 0; j < (int)dim1; ++j) {
            int index = i * dim1 + j;
            result_data[index] = data[index] + num;
        }
    }
    return Tensor(dim0, dim1, result_data);
}


Tensor Tensor::operator-(float num) {

    float result_data[dim0 * dim1] = {0,};
    for (int i = 0; i < (int)dim0; ++i) {
        for (int j = 0; j < (int)dim1; ++j) {
            int index = i * dim1 + j;
            result_data[index] = data[index] - num;
        }
    }
    return Tensor(dim0, dim1, result_data);
}


Tensor Tensor::operator*(float num) {
    float result_data[dim0 * dim1] = {0,};
    //float* result_data = new float[dim0 * dim1];
    for (int i = 0; i < (int)dim0; ++i) {
        for (int j = 0; j < (int)dim1; ++j) {
            int index = i * dim1 + j;
            result_data[index] = data[index] * num;
        }
    }
    return Tensor(dim0, dim1, result_data);
}


Tensor Tensor::operator/(float num) {

    assert (num != 0);

    float result_data[dim0 * dim1] = {0,};
    for (int i = 0; i < (int)dim0; ++i) {
        for (int j = 0; j < (int)dim1; ++j) {
            int index = i * dim1 + j;
            result_data[index] = data[index] / num;
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
            int index = i * dim1 + j;
            result_data[index] =\
                    (data[index] < other.data[index]) ? 1.0 : 0.0;
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
			int index = i * dim1 + j;
			result_data[index] =\
				(data[index] <= other.data[index]) ?\
				1.0 : 0.0;
		}
	}
	return Tensor(dim0, dim1, result_data);
}


Tensor Tensor::operator<=(float num) {
	float result_data[dim0 * dim1] = {0,};
	//float* result_data = new float[dim0 * dim1];
	for (int i = 0; i < (int)dim0; ++i) {
		for (int j = 0; j < (int)dim1; ++j) {
			int index = i * dim1 + j;
			result_data[index] =\
			    (data[index] <= num) ?\
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
			int index = i * dim1 + j;
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
			int index = i * dim1 + j;
			result_data[index] =\
				(data[index] >= other.data[index]) ?\
				1.0 : 0.0;
		}
	}
	return Tensor(dim0, dim1, result_data);
}

Tensor& Tensor::operator=(const Tensor& other) {
        if (dim0 != other.dim0 || dim1 != other.dim1) {
            dim0 = other.dim0;
            dim1 = other.dim1;
            if (data != nullptr) delete data; 
            data = new float[dim0 * dim1];
        }
	for (int i = 0; i < (int)dim0; ++i) {
		for (int j = 0; j < (int)dim1; ++j) {
			int index = i * dim1 + j;
			data[index] = other.data[index];
		}
	}
	return *this;
}

Tensor Tensor::max() {
    float max_data[1] = {data[0]};
    for (int i = 0; i < (int)dim0; ++i) {
        for (int j = 0; j < (int)dim1; ++j) {
            int index = i * dim1 + j;
            max_data[0] = max_data[0] >= data[index] ?\
                        max_data[0] : data[index];

        }
    }
    return Tensor(1, 1, max_data);
}

Tensor Tensor::sum(int axis) {
    //TODO if axis=None, return sum of all elements
    assert (axis == -1 or axis == 0 or axis == 1);

    if (axis == -1) {
        float sum[1] = {0};
        for (int i = 0; i < (int)dim0; ++i) {
            for (int j = 0; j < (int)dim1; ++j) {
                sum[0] += data[i * dim1 + j]; 
            }
        }
        return Tensor(1, 1, sum);
    }

    uint32_t result_dim = (axis == 0) ? dim1 : dim0;
    float result_data[result_dim] = {0,};
    if (axis == 0) {
        for (int i = 0; i < (int)dim0; ++i) {
            for (int j = 0; j < (int)dim1; ++j) {
                result_data[j] += data[i * dim1 + j]; 
            }
        }
        return Tensor(1, result_dim, result_data);
    }
    else {
        for (int i = 0; i < (int)dim0; ++i) {
            for (int j = 0; j < (int)dim1; ++j) {
                result_data[i] += data[i * dim1 + j];
            }
        }
        return Tensor(result_dim, 1, result_data);
    }
}

Tensor Tensor::dot(const Tensor& other) {
    assert (dim1 == other.dim0);
    float result_data[dim0 * other.dim1] = {0,}; 
    for (int i = 0; i < (int)dim0; ++i) {
        for (int j = 0; j < (int)other.dim1; ++j) {
            int index = i * other.dim1 + j;
            for (int k = 0; k < (int)dim1; ++k) {
                result_data[index] +=\
                    data[i * dim1 + k] * other.data[j + k * other.dim1];
            }
        }
    }
    return Tensor(dim0, other.dim1, result_data);
}

Tensor Tensor::T() {
    // TODO : improve for multi dimension
    float result_data[dim1 * dim0] = {0,};
    for (int i = 0; i < (int)dim0; ++i) {
        for (int j = 0; j < (int)dim1; ++j) {
            int cur_index = i * dim1 + j;
            int result_index = j * dim0 + i;
            result_data[result_index] = data[cur_index];
        }
    }
    return Tensor(dim1, dim0, result_data);
}


/* 
 * Tensor operator 
 *
 */
Tensor zeros(uint32_t dim0, uint32_t dim1) {
    float zero_data[dim0 * dim1] = {0,};
    return Tensor(dim0, dim1, zero_data);
}
Tensor operator+(float num, Tensor tensor) {
    return tensor + num;
}
Tensor operator-(float num, Tensor tensor) {
    uint32_t dim0 = tensor.get_dim0(); 
    uint32_t dim1 = tensor.get_dim1(); 
    float num_data[dim0 * dim1] = {0, };  
    for (int i = 0; i < (int)dim0; ++i) {
        for (int j = 0; j < (int)dim1; ++j) {
            int index = i * dim1 + j;
            num_data[index] = num;
        }
    }
    Tensor num_tensor(dim0, dim1, num_data);
    return num_tensor - tensor;
}
Tensor operator*(float num, Tensor tensor) {
    return tensor * num;
}
Tensor operator/(float num, Tensor tensor) {
    uint32_t dim0 = tensor.get_dim0(); 
    uint32_t dim1 = tensor.get_dim1(); 
    float num_data[dim0 * dim1] = {0, };  
    for (int i = 0; i < (int)dim0; ++i) {
        for (int j = 0; j < (int)dim1; ++j) {
            int index = i * dim1 + j;
            num_data[index] = num;
        }
    }
    Tensor num_tensor(dim0, dim1, num_data);
    return num_tensor / tensor;
}

Tensor reverse_boolean(Tensor tensor) {
    uint32_t dim0 = tensor.get_dim0(); 
    uint32_t dim1 = tensor.get_dim1(); 
    float result_data[dim0 * dim1] = {0,};
    for (int i = 0; i < (int)dim0; ++i) {
        for (int j = 0; j < (int)dim1; ++j) {
            int index = i * dim1 + j;
            result_data[index] =\
                    tensor(i, j) == 1 ? 0 : 1;
        }
    }
    return Tensor(dim0, dim1, result_data);
}

Tensor exp(Tensor tensor) {
    //TODO how to get reference input.
    uint32_t dim0 = tensor.get_dim0(); 
    uint32_t dim1 = tensor.get_dim1(); 
    float result_data[dim0 * dim1] = {0,};
    for (int i = 0; i < (int)dim0; ++i) {
        for (int j = 0; j < (int)dim1; ++j) {
            int index = i * dim1 + j;
            result_data[index] = std::exp(tensor(i, j));
        }
    }
    return Tensor(dim0, dim1, result_data);
}

Tensor log(Tensor tensor) {
    uint32_t dim0 = tensor.get_dim0(); 
    uint32_t dim1 = tensor.get_dim1(); 
    float result_data[dim0 * dim1] = {0,};
    for (int i = 0; i < (int)dim0; ++i) {
        for (int j = 0; j < (int)dim1; ++j) {
            int index = i * dim1 + j;
            result_data[index] = std::log(tensor(i, j));
        }
    }
    return Tensor(dim0, dim1, result_data);
}
