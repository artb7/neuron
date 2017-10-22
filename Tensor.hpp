#ifndef _TENSOR_H_
#define _TENSOR_H_

#include <assert.h>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <stdint.h>

#include "Mat2d.hpp"

/******* Template version *******/
//TODO
struct Shape {
};

template <class data_type=float>
class Tensor {
public: 
    Tensor();
	Tensor(uint32_t dim0, uint32_t dim1, uint32_t dim2, data_type* data);
	Tensor(uint32_t dim0, uint32_t dim1, uint32_t dim2, uint32_t dim3, data_type* data);
	~Tensor();
	Tensor(const Tensor& other);
	Tensor<data_type>& operator = (const Tensor& other);

	uint32_t get_row();
	uint32_t get_col();

	Tensor operator - ();

	data_type& operator () (uint32_t row, uint32_t col);
	Tensor operator [] (const Tensor& other);

	Tensor operator + (const Tensor& other);
	Tensor operator - (const Tensor& other);
	Tensor operator * (const Tensor& other);
	Tensor operator / (const Tensor& other);
	Tensor operator < (const Tensor& other);
	Tensor operator <= (const Tensor& other);
	Tensor operator > (const Tensor& other);
	Tensor operator >= (const Tensor& other);
	Tensor operator == (const Tensor& other);
	Tensor operator != (const Tensor& other);

	Tensor operator + (data_type num);
	Tensor operator - (data_type num);
	Tensor operator * (data_type num);
	Tensor operator / (data_type num);
	Tensor operator < (data_type num);
	Tensor operator <= (data_type num);
	Tensor operator > (data_type num);
	Tensor operator >= (data_type num);
	Tensor operator == (data_type num);
	Tensor operator != (data_type num);

    Tensor max();
    Tensor sum(int axis=-1);

	Tensor dot(const Tensor& other);
    Tensor T();

private:
    Mat2d<data_type>* data;
	uint32_t dim0;
	uint32_t dim1;
	uint32_t dim2;
	uint32_t dim3;
};

template <class data_type>
Tensor<data_type>::Tensor() {
    this->dim0 = 0;
    this->dim1 = 0;
    this->dim2 = 0;
    this->dim3 = 0;
    this->data = nullptr;
}

template <class data_type>
Tensor<data_type>::Tensor(uint32_t dim0, uint32_t dim1, 
                          uint32_t dim2, uint32_t dim3, data_type* data) {

    this->dim0 = dim0;
    this->dim1 = dim1;
    this->dim2 = dim2;
    this->dim3 = dim3;
    this->data = new Mat2d<data_type>(dim2, dim3, data_type* );

    for (int i = 0; i < (int)dim; ++i) {
        for (int j = 0; j < (int)col; ++j) {
            int index = (int)col * i + j;
            this->data[index] = data[index];
            //std::cout << index << " :";
            //std::cout << data[index] << " ";
        }
        //std::cout << std::endl;
    }
}

template <class data_type>
Tensor<data_type>::~Tensor() {
    if (data != nullptr)
        delete data;
}

template <class data_type>
Tensor<data_type>::Tensor(const Tensor& other) {
    //std::cout << "hello" << std::endl;
    this->row = other.row;
    this->col = other.col;
    this->data = new data_type[row * col];
    for (int i = 0; i < (int)row; ++i) {
        for (int j = 0; j < (int)col; ++j) {
            int index = (int)col * i + j;
            this->data[index] = other.data[index];
        }
    }
}

template <class data_type>
Tensor<data_type>& Tensor<data_type>::operator = (const Tensor& other) {
        if (row != other.row || col != other.col) {
            row = other.row;
            col = other.col;
            if (data != nullptr) delete data; 
            data = new data_type[row * col];
        }
	for (int i = 0; i < (int)row; ++i) {
		for (int j = 0; j < (int)col; ++j) {
			int index = i * col + j;
			data[index] = other.data[index];
		}
	}
	return *this;
}

template <class data_type>
uint32_t Tensor<data_type>::get_row() { 
    return this->row;
}

template <class data_type>
uint32_t Tensor<data_type>::get_col() {
    return this->col;
}


template <class data_type>
Tensor<data_type> Tensor<data_type>::operator - () {
    data_type result_data[row * col] = {0,};
    for (int i = 0; i < (int)row; ++i) {
        for (int j = 0; j < (int)col; ++j) {
            int index = i * col + j;
            result_data[index] = -data[index];
        }
    }
    return Tensor<data_type>(row, col, result_data);
}

template <class data_type>
data_type& Tensor<data_type>::operator () (uint32_t row, uint32_t col) {
    assert (row < this->row && col < this->col);
    return data[row * this->col + col];	
}

template <class data_type>
Tensor<data_type> Tensor<data_type>::operator [] (const Tensor<data_type>& other) {
    assert (row == other.row && col == other.col);
	data_type result_data[row * col] = {0,};
        // TODO 1 -> true
	for (int i = 0; i < (int)row; ++i) {
		for (int j = 0; j < (int)col; ++j) {
			int index = i * col + j;
			if (other.data[index] == 1)
				result_data[index] = data[index];
			else
				result_data[index] = 0;
		}
	}
        // TODO return tensor is not self.
        // how to implement numpy indexing
	return Tensor<data_type>(row, col, result_data);
}

template <class data_type>
Tensor<data_type> Tensor<data_type>::operator + (const Tensor<data_type>& other) {
    assert ((row == other.row && col == other.col) or\
            (row == other.row && other.col == 1) or\
            (col == other.col && other.row == 1));
    data_type result_data[row * col] = {0,};
    if (row == other.row && other.col == 1) {
        for (int i = 0; i < (int)row; ++i) {
            for (int j = 0; j < (int)col; ++j) {
                int index = col * i + j;
                result_data[index] = data[index] + other.data[i];
            }
        }
    }
    else if (col == other.col && other.row == 1) {
        for (int i = 0; i < (int)row; ++i) {
            for (int j = 0; j < (int)col; ++j) {
                int index = col * i + j;
                result_data[index] = data[index] + other.data[j];
            }
        }
    }
    else {
        for (int i = 0; i < (int)row; ++i) {
            for (int j = 0; j < (int)col; ++j) {
                int index = col * i + j;
                result_data[index] = data[index] + other.data[index];
            }
        }
    }
    return Tensor<data_type>(row, col, result_data);
}


template <class data_type>
Tensor<data_type> Tensor<data_type>::operator - (const Tensor<data_type>& other) {
    assert ((row == other.row && col == other.col) or\
            (row == other.row && other.col == 1) or\
            (col == other.col && other.row == 1));
    data_type result_data[row * col] = {0,};
    if (row == other.row && other.col == 1) {
        for (int i = 0; i < (int)row; ++i) {
            for (int j = 0; j < (int)col; ++j) {
                int index = col * i + j;
                result_data[index] = data[index] - other.data[i];
            }
        }
    }
    else if (col == other.col && other.row == 1) {
        for (int i = 0; i < (int)row; ++i) {
            for (int j = 0; j < (int)col; ++j) {
                int index = col * i + j;
                result_data[index] = data[index] - other.data[j];
            }
        }
    }
    else {
        for (int i = 0; i < (int)row; ++i) {
            for (int j = 0; j < (int)col; ++j) {
                int index = col * i + j;
                result_data[index] = data[index] - other.data[index];
            }
        }
    }
    return Tensor<data_type>(row, col, result_data);
}


template <class data_type>
Tensor<data_type> Tensor<data_type>::operator * (const Tensor<data_type>& other) {
    assert ((row == other.row && col == other.col) or\
            (row == other.row && other.col == 1) or\
            (col == other.col && other.row == 1));
    data_type result_data[row * col] = {0,};
    if (row == other.row && other.col == 1) {
        for (int i = 0; i < (int)row; ++i) {
            for (int j = 0; j < (int)col; ++j) {
                int index = col * i + j;
                result_data[index] = data[index] * other.data[i];
            }
        }
    }
    else if (col == other.col && other.row == 1) {
        for (int i = 0; i < (int)row; ++i) {
            for (int j = 0; j < (int)col; ++j) {
                int index = col * i + j;
                result_data[index] = data[index] * other.data[j];
            }
        }
    }
    else {
        for (int i = 0; i < (int)row; ++i) {
            for (int j = 0; j < (int)col; ++j) {
                int index = col * i + j;
                result_data[index] = data[index] * other.data[index];
            }
        }
    }
    return Tensor<data_type>(row, col, result_data);
}


template <class data_type>
Tensor<data_type> Tensor<data_type>::operator / (const Tensor<data_type>& other) {
    assert ((row == other.row && col == other.col) or\
            (row == other.row && other.col == 1) or\
            (col == other.col && other.row == 1));
    for (int i = 0; i < (int)row; ++i) {
        for(int j = 0; j < (int)col; ++j) {
            if (other.data[i * col + j] == 0) { 
                throw "Zero division Error";
            }
        }
    }

    data_type result_data[row * col] = {0,};
    if (row == other.row && other.col == 1) {
        for (int i = 0; i < (int)row; ++i) {
            for (int j = 0; j < (int)col; ++j) {
                int index = col * i + j;
                result_data[index] = data[index] / other.data[i];
            }
        }
    }
    else if (col == other.col && other.row == 1) {
        for (int i = 0; i < (int)row; ++i) {
            for (int j = 0; j < (int)col; ++j) {
                int index = col * i + j;
                result_data[index] = data[index] / other.data[j];
            }
        }
    }
    else {
        for (int i = 0; i < (int)row; ++i) {
            for (int j = 0; j < (int)col; ++j) {
                int index = col * i + j;
                result_data[index] = data[index] / other.data[index];
            }
        }
    }
    return Tensor<data_type>(row, col, result_data);
}




template <class data_type>
Tensor<data_type> Tensor<data_type>::operator < (const Tensor<data_type>& other) {	
    assert (row == other.row && col == other.col);
    data_type result_data[row * col] = {0,};
    //data_type* result_data = new data_type[row * col];
    for (int i = 0; i < (int)row; ++i) {
        for (int j = 0; j < (int)col; ++j) {
            int index = i * col + j;
            result_data[index] =\
                    (data[index] < other.data[index]) ? 1.0 : 0.0;
            }
    }
    return Tensor<data_type>(row, col, result_data);
}

template <class data_type>
Tensor<data_type> Tensor<data_type>::operator <= (const Tensor<data_type>& other) {
	assert (row == other.row && col == other.col);
	data_type result_data[row * col] = {0,};
	//data_type* result_data = new data_type[row * col];
	for (int i = 0; i < (int)row; ++i) {
		for (int j = 0; j < (int)col; ++j) {
			int index = i * col + j;
			result_data[index] =\
				(data[index] <= other.data[index]) ? 1.0 : 0.0;
		}
	}
	return Tensor<data_type>(row, col, result_data);
}

template <class data_type>
Tensor<data_type> Tensor<data_type>::operator > (const Tensor<data_type>& other) {
	assert (row == other.row && col == other.col);
	data_type result_data[row * col] = {0,};
	//data_type* result_data = new data_type[row * col];
	for (int i = 0; i < (int)row; ++i) {
		for (int j = 0; j < (int)col; ++j) {
			int index = i * col + j;
			result_data[index] =\
				(data[index] > other.data[index]) ? 1.0 : 0.0;
		}
	}
	return Tensor<data_type>(row, col, result_data);
}

template <class data_type>
Tensor<data_type> Tensor<data_type>::operator >= (const Tensor<data_type>& other) {
	assert (row == other.row && col == other.col);
	data_type result_data[row * col] = {0,};
	//data_type* result_data = new data_type[row * col];
	for (int i = 0; i < (int)row; ++i) {
		for (int j = 0; j < (int)col; ++j) {
			int index = i * col + j;
			result_data[index] =\
				(data[index] >= other.data[index]) ? 1.0 : 0.0;
		}
	}
	return Tensor<data_type>(row, col, result_data);
}

template <class data_type>
Tensor<data_type> Tensor<data_type>::operator == (const Tensor<data_type>& other) {
	assert (row == other.row && col == other.col);
	data_type result_data[row * col] = {0,};
	for (int i = 0; i < (int)row; ++i) {
		for (int j = 0; j < (int)col; ++j) {
			int index = i * col + j;
			result_data[index] =\
				(data[index] == other.data[index]) ? 1.0 : 0.0;
		}
	}
	return Tensor<data_type>(row, col, result_data);
}

template <class data_type>
Tensor<data_type> Tensor<data_type>::operator != (const Tensor<data_type>& other) {
	assert (row == other.row && col == other.col);
	data_type result_data[row * col] = {0,};
	//data_type* result_data = new data_type[row * col];
	for (int i = 0; i < (int)row; ++i) {
		for (int j = 0; j < (int)col; ++j) {
			int index = i * col + j;
			result_data[index] =\
				(data[index] != other.data[index]) ? 1.0 : 0.0;
		}
	}
	return Tensor<data_type>(row, col, result_data);
}


template <class data_type>
Tensor<data_type> Tensor<data_type>::operator + (data_type num) {

    data_type result_data[row * col] = {0,};
    for (int i = 0; i < (int)row; ++i) {
        for (int j = 0; j < (int)col; ++j) {
            int index = i * col + j;
            result_data[index] = data[index] + num;
        }
    }
    return Tensor<data_type>(row, col, result_data);
}


template <class data_type>
Tensor<data_type> Tensor<data_type>::operator - (data_type num) {

    data_type result_data[row * col] = {0,};
    for (int i = 0; i < (int)row; ++i) {
        for (int j = 0; j < (int)col; ++j) {
            int index = i * col + j;
            result_data[index] = data[index] - num;
        }
    }
    return Tensor<data_type>(row, col, result_data);
}


template <class data_type>
Tensor<data_type> Tensor<data_type>::operator * (data_type num) {
    data_type result_data[row * col] = {0,};
    for (int i = 0; i < (int)row; ++i) {
        for (int j = 0; j < (int)col; ++j) {
            int index = i * col + j;
            result_data[index] = data[index] * num;
        }
    }
    return Tensor<data_type>(row, col, result_data);
}


template <class data_type>
Tensor<data_type> Tensor<data_type>::operator / (data_type num) {

    assert (num != 0);

    data_type result_data[row * col] = {0,};
    for (int i = 0; i < (int)row; ++i) {
        for (int j = 0; j < (int)col; ++j) {
            int index = i * col + j;
            result_data[index] = data[index] / num;
        }
    }
    return Tensor<data_type>(row, col, result_data);
}

template <class data_type>
Tensor<data_type> Tensor<data_type>::operator < (data_type num) {
	data_type result_data[row * col] = {0,};
	for (int i = 0; i < (int)row; ++i) {
		for (int j = 0; j < (int)col; ++j) {
			int index = i * col + j;
			result_data[index] = (data[index] < num) ? 1.0 : 0.0;
		}
	}
	return Tensor<data_type>(row, col, result_data);
}

template <class data_type>
Tensor<data_type> Tensor<data_type>::operator <= (data_type num) {
	data_type result_data[row * col] = {0,};
	for (int i = 0; i < (int)row; ++i) {
		for (int j = 0; j < (int)col; ++j) {
			int index = i * col + j;
			result_data[index] = (data[index] <= num) ? 1.0 : 0.0;
		}
	}
	return Tensor<data_type>(row, col, result_data);
}

template <class data_type>
Tensor<data_type> Tensor<data_type>::operator > (data_type num) {
	data_type result_data[row * col] = {0,};
	for (int i = 0; i < (int)row; ++i) {
		for (int j = 0; j < (int)col; ++j) {
			int index = i * col + j;
			result_data[index] = (data[index] > num) ? 1.0 : 0.0;
		}
	}
	return Tensor<data_type>(row, col, result_data);
}

template <class data_type>
Tensor<data_type> Tensor<data_type>::operator >= (data_type num) {
	data_type result_data[row * col] = {0,};
	for (int i = 0; i < (int)row; ++i) {
		for (int j = 0; j < (int)col; ++j) {
			int index = i * col + j;
			result_data[index] = (data[index] >= num) ? 1.0 : 0.0;
		}
	}
	return Tensor<data_type>(row, col, result_data);
}
template <class data_type>
Tensor<data_type> Tensor<data_type>::operator == (data_type num) {
	data_type result_data[row * col] = {0,};
	for (int i = 0; i < (int)row; ++i) {
		for (int j = 0; j < (int)col; ++j) {
			int index = i * col + j;
			result_data[index] = (data[index] == num) ? 1.0 : 0.0;
		}
	}
	return Tensor<data_type>(row, col, result_data);
}
template <class data_type>
Tensor<data_type> Tensor<data_type>::operator != (data_type num) {
	data_type result_data[row * col] = {0,};
	for (int i = 0; i < (int)row; ++i) {
		for (int j = 0; j < (int)col; ++j) {
			int index = i * col + j;
			result_data[index] = (data[index] != num) ? 1.0 : 0.0;
		}
	}
	return Tensor<data_type>(row, col, result_data);
}

template <class data_type>
Tensor<data_type> Tensor<data_type>::max() {
    data_type max_data[1] = {data[0]};
    for (int i = 0; i < (int)row; ++i) {
        for (int j = 0; j < (int)col; ++j) {
            int index = i * col + j;
            max_data[0] = max_data[0] >= data[index] ?\
                            max_data[0] : data[index];

        }
    }
    return Tensor<data_type>(1, 1, max_data);
}

template <class data_type>
Tensor<data_type> Tensor<data_type>::sum(int axis) {
    //TODO if axis=None, return sum of all elements
    assert (axis == -1 or axis == 0 or axis == 1);

    if (axis == -1) {
        data_type sum[1] = {0};
        for (int i = 0; i < (int)row; ++i) {
            for (int j = 0; j < (int)col; ++j) {
                sum[0] += data[i * col + j]; 
            }
        }
        return Tensor<data_type>(1, 1, sum);
    }

    uint32_t result_dim = (axis == 0) ? col : row;
    data_type result_data[result_dim] = {0,};
    if (axis == 0) {
        for (int i = 0; i < (int)row; ++i) {
            for (int j = 0; j < (int)col; ++j) {
                result_data[j] += data[i * col + j]; 
            }
        }
        return Tensor<data_type>(1, result_dim, result_data);
    }
    else {
        for (int i = 0; i < (int)row; ++i) {
            for (int j = 0; j < (int)col; ++j) {
                result_data[i] += data[i * col + j];
            }
        }
        return Tensor<data_type>(result_dim, 1, result_data);
    }
}

template <class data_type>
Tensor<data_type> Tensor<data_type>::dot(const Tensor<data_type>& other) {
    assert (col == other.row);
    data_type result_data[row * other.col] = {0,}; 
    for (int i = 0; i < (int)row; ++i) {
        for (int j = 0; j < (int)other.col; ++j) {
            int index = i * other.col + j;
            for (int k = 0; k < (int)col; ++k) {
                result_data[index] +=\
                    data[i * col + k] * other.data[j + k * other.col];
            }
        }
    }
    return Tensor<data_type>(row, other.col, result_data);
}

template <class data_type>
Tensor<data_type> Tensor<data_type>::T() {
    // TODO : improve for multi dimension
    data_type result_data[col * row] = {0,};
    for (int i = 0; i < (int)row; ++i) {
        for (int j = 0; j < (int)col; ++j) {
            int cur_index = i * col + j;
            int result_index = j * row + i;
            result_data[result_index] = data[cur_index];
        }
    }
    return Tensor<data_type>(col, row, result_data);
}


/* 
 * Tensor operator 
 *
 */
template <class data_type>
Tensor<data_type> zeros(uint32_t row, uint32_t col) {
    data_type zero_data[row * col] = {0,};
    return Tensor<data_type>(row, col, zero_data);
}
template <class data_type>
Tensor<data_type> operator+(data_type num, Tensor<data_type> tensor) {
    return tensor + num;
}
template <class data_type>
Tensor<data_type> operator-(data_type num, Tensor<data_type> tensor) {
    uint32_t row = tensor.get_row(); 
    uint32_t col = tensor.get_col(); 
    data_type num_data[row * col] = {0, };  
    for (int i = 0; i < (int)row; ++i) {
        for (int j = 0; j < (int)col; ++j) {
            int index = i * col + j;
            num_data[index] = num;
        }
    }
    Tensor<data_type> num_tensor(row, col, num_data);
    return num_tensor - tensor;
}
template <class data_type>
Tensor<data_type> operator*(data_type num, Tensor<data_type> tensor) {
    return tensor * num;
}
template <class data_type>
Tensor<data_type> operator/(data_type num, Tensor<data_type> tensor) {
    uint32_t row = tensor.get_row(); 
    uint32_t col = tensor.get_col(); 
    data_type num_data[row * col] = {0, };  
    for (int i = 0; i < (int)row; ++i) {
        for (int j = 0; j < (int)col; ++j) {
            int index = i * col + j;
            num_data[index] = num;
        }
    }
    Tensor<data_type> num_tensor(row, col, num_data);
    return num_tensor / tensor;
}

template <class data_type>
Tensor<data_type> reverse_boolean(Tensor<data_type> tensor) {
    uint32_t row = tensor.get_row(); 
    uint32_t col = tensor.get_col(); 
    data_type result_data[row * col] = {0,};
    for (int i = 0; i < (int)row; ++i) {
        for (int j = 0; j < (int)col; ++j) {
            int index = i * col + j;
            result_data[index] =\
                    tensor(i, j) == 1 ? 0 : 1;
        }
    }
    return Tensor<data_type>(row, col, result_data);
}

template <class data_type>
Tensor<data_type> exp(Tensor<data_type> tensor) {
    //TODO how to get reference input.
    uint32_t row = tensor.get_row(); 
    uint32_t col = tensor.get_col(); 
    data_type result_data[row * col] = {0,};
    for (int i = 0; i < (int)row; ++i) {
        for (int j = 0; j < (int)col; ++j) {
            int index = i * col + j;
            result_data[index] = std::exp(tensor(i, j));
        }
    }
    return Tensor<data_type>(row, col, result_data);
}

template <class data_type>
Tensor<data_type> log(Tensor<data_type> tensor) {
    uint32_t row = tensor.get_row(); 
    uint32_t col = tensor.get_col(); 
    data_type result_data[row * col] = {0,};
    for (int i = 0; i < (int)row; ++i) {
        for (int j = 0; j < (int)col; ++j) {
            int index = i * col + j;
            result_data[index] = std::log(tensor(i, j));
        }
    }
    return Tensor<data_type>(row, col, result_data);
}

#endif // _TENSOR_H_
