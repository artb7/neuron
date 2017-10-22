#ifndef _MAT2D_H_
#define _MAT2D_H_

#include <assert.h>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <stdint.h>

/*
class Mat2d { public: 
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
*/

/******* Template version *******/
template <class data_type=float>
class Mat2d {
public: 
    Mat2d();
	Mat2d(uint32_t row, uint32_t col, data_type* data);
	~Mat2d();
	Mat2d(const Mat2d& other);
	Mat2d<data_type>& operator = (const Mat2d& other);

	uint32_t get_row();
	uint32_t get_col();

    //void operator << (const Mat2d& t);

	Mat2d operator - ();
    Mat2d operator ! ();

	data_type& operator () (uint32_t row, uint32_t col);
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

	Mat2d operator + (data_type num);
	Mat2d operator - (data_type num);
	Mat2d operator * (data_type num);
	Mat2d operator / (data_type num);
	Mat2d operator < (data_type num);
	Mat2d operator <= (data_type num);
	Mat2d operator > (data_type num);
	Mat2d operator >= (data_type num);
	Mat2d operator == (data_type num);
	Mat2d operator != (data_type num);

    Mat2d max();
    Mat2d sum(int axis=-1);

	Mat2d dot(const Mat2d& other);
    Mat2d T();

    void print();

private:
	data_type* data;
	uint32_t row;
	uint32_t col;
};

template <class data_type>
Mat2d<data_type>::Mat2d() {
    this->row = 0;
    this->col = 0;
    this->data = nullptr;
}

template <class data_type>
Mat2d<data_type>::Mat2d(uint32_t row, uint32_t col, data_type* data) {
    //std::cout << "hello" << std::endl;
    this->row = row;
    this->col = col;
    this->data = new data_type[row * col];
    for (int i = 0; i < (int)row; ++i) {
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
Mat2d<data_type>::~Mat2d() {
    if (data != nullptr)
        delete data;
}

template <class data_type>
Mat2d<data_type>::Mat2d(const Mat2d& other) {
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
Mat2d<data_type>& Mat2d<data_type>::operator = (const Mat2d& other) {
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
uint32_t Mat2d<data_type>::get_row() { 
    return this->row;
}

template <class data_type>
uint32_t Mat2d<data_type>::get_col() {
    return this->col;
}


template <class data_type>
Mat2d<data_type> Mat2d<data_type>::operator - () {
    data_type result_data[row * col] = {0,};
    for (int i = 0; i < (int)row; ++i) {
        for (int j = 0; j < (int)col; ++j) {
            int index = i * col + j;
            result_data[index] = -data[index];
        }
    }
    return Mat2d<data_type>(row, col, result_data);
}

template <class data_type>
Mat2d<data_type> Mat2d<data_type>::operator ! () {
    //TODO improve
    data_type result_data[row * col] = {0,};
    for (int i = 0; i < (int)row; ++i) {
        for (int j = 0; j < (int)col; ++j) {
            int index = i * col + j;
            result_data[index] = (data[index] == 1) ? 0 : 1;
        }
    }
    return Mat2d<data_type>(row, col, result_data);
}

template <class data_type>
data_type& Mat2d<data_type>::operator () (uint32_t row, uint32_t col) {
    assert (row < this->row && col < this->col);
    return data[row * this->col + col];	
}

template <class data_type>
Mat2d<data_type> Mat2d<data_type>::operator [] (const Mat2d<data_type>& other) {
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
	return Mat2d<data_type>(row, col, result_data);
}

template <class data_type>
Mat2d<data_type> Mat2d<data_type>::operator + (const Mat2d<data_type>& other) {
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
    return Mat2d<data_type>(row, col, result_data);
}


template <class data_type>
Mat2d<data_type> Mat2d<data_type>::operator - (const Mat2d<data_type>& other) {
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
    return Mat2d<data_type>(row, col, result_data);
}


template <class data_type>
Mat2d<data_type> Mat2d<data_type>::operator * (const Mat2d<data_type>& other) {
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
    return Mat2d<data_type>(row, col, result_data);
}


template <class data_type>
Mat2d<data_type> Mat2d<data_type>::operator / (const Mat2d<data_type>& other) {
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
    return Mat2d<data_type>(row, col, result_data);
}




template <class data_type>
Mat2d<data_type> Mat2d<data_type>::operator < (const Mat2d<data_type>& other) {	
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
    return Mat2d<data_type>(row, col, result_data);
}

template <class data_type>
Mat2d<data_type> Mat2d<data_type>::operator <= (const Mat2d<data_type>& other) {
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
	return Mat2d<data_type>(row, col, result_data);
}

template <class data_type>
Mat2d<data_type> Mat2d<data_type>::operator > (const Mat2d<data_type>& other) {
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
	return Mat2d<data_type>(row, col, result_data);
}

template <class data_type>
Mat2d<data_type> Mat2d<data_type>::operator >= (const Mat2d<data_type>& other) {
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
	return Mat2d<data_type>(row, col, result_data);
}

template <class data_type>
Mat2d<data_type> Mat2d<data_type>::operator == (const Mat2d<data_type>& other) {
	assert (row == other.row && col == other.col);
	data_type result_data[row * col] = {0,};
	for (int i = 0; i < (int)row; ++i) {
		for (int j = 0; j < (int)col; ++j) {
			int index = i * col + j;
			result_data[index] =\
				(data[index] == other.data[index]) ? 1.0 : 0.0;
		}
	}
	return Mat2d<data_type>(row, col, result_data);
}

template <class data_type>
Mat2d<data_type> Mat2d<data_type>::operator != (const Mat2d<data_type>& other) {
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
	return Mat2d<data_type>(row, col, result_data);
}


template <class data_type>
Mat2d<data_type> Mat2d<data_type>::operator + (data_type num) {

    data_type result_data[row * col] = {0,};
    for (int i = 0; i < (int)row; ++i) {
        for (int j = 0; j < (int)col; ++j) {
            int index = i * col + j;
            result_data[index] = data[index] + num;
        }
    }
    return Mat2d<data_type>(row, col, result_data);
}


template <class data_type>
Mat2d<data_type> Mat2d<data_type>::operator - (data_type num) {

    data_type result_data[row * col] = {0,};
    for (int i = 0; i < (int)row; ++i) {
        for (int j = 0; j < (int)col; ++j) {
            int index = i * col + j;
            result_data[index] = data[index] - num;
        }
    }
    return Mat2d<data_type>(row, col, result_data);
}


template <class data_type>
Mat2d<data_type> Mat2d<data_type>::operator * (data_type num) {
    data_type result_data[row * col] = {0,};
    for (int i = 0; i < (int)row; ++i) {
        for (int j = 0; j < (int)col; ++j) {
            int index = i * col + j;
            result_data[index] = data[index] * num;
        }
    }
    return Mat2d<data_type>(row, col, result_data);
}


template <class data_type>
Mat2d<data_type> Mat2d<data_type>::operator / (data_type num) {

    assert (num != 0);

    data_type result_data[row * col] = {0,};
    for (int i = 0; i < (int)row; ++i) {
        for (int j = 0; j < (int)col; ++j) {
            int index = i * col + j;
            result_data[index] = data[index] / num;
        }
    }
    return Mat2d<data_type>(row, col, result_data);
}

template <class data_type>
Mat2d<data_type> Mat2d<data_type>::operator < (data_type num) {
	data_type result_data[row * col] = {0,};
	for (int i = 0; i < (int)row; ++i) {
		for (int j = 0; j < (int)col; ++j) {
			int index = i * col + j;
			result_data[index] = (data[index] < num) ? 1.0 : 0.0;
		}
	}
	return Mat2d<data_type>(row, col, result_data);
}

template <class data_type>
Mat2d<data_type> Mat2d<data_type>::operator <= (data_type num) {
	data_type result_data[row * col] = {0,};
	for (int i = 0; i < (int)row; ++i) {
		for (int j = 0; j < (int)col; ++j) {
			int index = i * col + j;
			result_data[index] = (data[index] <= num) ? 1.0 : 0.0;
		}
	}
	return Mat2d<data_type>(row, col, result_data);
}

template <class data_type>
Mat2d<data_type> Mat2d<data_type>::operator > (data_type num) {
	data_type result_data[row * col] = {0,};
	for (int i = 0; i < (int)row; ++i) {
		for (int j = 0; j < (int)col; ++j) {
			int index = i * col + j;
			result_data[index] = (data[index] > num) ? 1.0 : 0.0;
		}
	}
	return Mat2d<data_type>(row, col, result_data);
}

template <class data_type>
Mat2d<data_type> Mat2d<data_type>::operator >= (data_type num) {
	data_type result_data[row * col] = {0,};
	for (int i = 0; i < (int)row; ++i) {
		for (int j = 0; j < (int)col; ++j) {
			int index = i * col + j;
			result_data[index] = (data[index] >= num) ? 1.0 : 0.0;
		}
	}
	return Mat2d<data_type>(row, col, result_data);
}
template <class data_type>
Mat2d<data_type> Mat2d<data_type>::operator == (data_type num) {
	data_type result_data[row * col] = {0,};
	for (int i = 0; i < (int)row; ++i) {
		for (int j = 0; j < (int)col; ++j) {
			int index = i * col + j;
			result_data[index] = (data[index] == num) ? 1.0 : 0.0;
		}
	}
	return Mat2d<data_type>(row, col, result_data);
}
template <class data_type>
Mat2d<data_type> Mat2d<data_type>::operator != (data_type num) {
	data_type result_data[row * col] = {0,};
	for (int i = 0; i < (int)row; ++i) {
		for (int j = 0; j < (int)col; ++j) {
			int index = i * col + j;
			result_data[index] = (data[index] != num) ? 1.0 : 0.0;
		}
	}
	return Mat2d<data_type>(row, col, result_data);
}

template <class data_type>
Mat2d<data_type> Mat2d<data_type>::max() {
    data_type max_data[1] = {data[0]};
    for (int i = 0; i < (int)row; ++i) {
        for (int j = 0; j < (int)col; ++j) {
            int index = i * col + j;
            max_data[0] = max_data[0] >= data[index] ?\
                            max_data[0] : data[index];

        }
    }
    return Mat2d<data_type>(1, 1, max_data);
}

template <class data_type>
Mat2d<data_type> Mat2d<data_type>::sum(int axis) {
    //TODO if axis=None, return sum of all elements
    assert (axis == -1 or axis == 0 or axis == 1);

    if (axis == -1) {
        data_type sum[1] = {0};
        for (int i = 0; i < (int)row; ++i) {
            for (int j = 0; j < (int)col; ++j) {
                sum[0] += data[i * col + j]; 
            }
        }
        return Mat2d<data_type>(1, 1, sum);
    }

    uint32_t result_dim = (axis == 0) ? col : row;
    data_type result_data[result_dim] = {0,};
    if (axis == 0) {
        for (int i = 0; i < (int)row; ++i) {
            for (int j = 0; j < (int)col; ++j) {
                result_data[j] += data[i * col + j]; 
            }
        }
        return Mat2d<data_type>(1, result_dim, result_data);
    }
    else {
        for (int i = 0; i < (int)row; ++i) {
            for (int j = 0; j < (int)col; ++j) {
                result_data[i] += data[i * col + j];
            }
        }
        return Mat2d<data_type>(result_dim, 1, result_data);
    }
}

template <class data_type>
Mat2d<data_type> Mat2d<data_type>::dot(const Mat2d<data_type>& other) {
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
    return Mat2d<data_type>(row, other.col, result_data);
}

template <class data_type>
Mat2d<data_type> Mat2d<data_type>::T() {
    // TODO : improve for multi dimension
    data_type result_data[col * row] = {0,};
    for (int i = 0; i < (int)row; ++i) {
        for (int j = 0; j < (int)col; ++j) {
            int cur_index = i * col + j;
            int result_index = j * row + i;
            result_data[result_index] = data[cur_index];
        }
    }
    return Mat2d<data_type>(col, row, result_data);
}


template <class data_type>
void Mat2d<data_type>::print() {
    for (int i = 0; i < (int)row; ++i) {
        for (int j = 0; j < (int)col; ++j) {
            int index = i * col + j;
            std::cout << data[index] << " ";	
        }
        std::cout << std::endl;
    }
    return;
}


/******* Mat2d operator  *******/
namespace Mat {

    inline
    Mat2d<float> zeros(uint32_t row, uint32_t col) {
        float zero_data[row * col] = {0,};
        return Mat2d<float>(row, col, zero_data);
    }

    inline
    Mat2d<float> ones(uint32_t row, uint32_t col) {
        float one_data[row * col] = {0,};
        for (int i = 0; i < int(row * col); ++i) {
            one_data[i] = 1;
        }
        return Mat2d<float>(row, col, one_data);
    }

    template <class data_type>
    Mat2d<data_type> exp(Mat2d<data_type> tensor) {
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
        return Mat2d<data_type>(row, col, result_data);
    }

    template <class data_type>
    Mat2d<data_type> log(Mat2d<data_type> tensor) {
        uint32_t row = tensor.get_row(); 
        uint32_t col = tensor.get_col(); 
        data_type result_data[row * col] = {0,};
        for (int i = 0; i < (int)row; ++i) {
            for (int j = 0; j < (int)col; ++j) {
                int index = i * col + j;
                result_data[index] = std::log(tensor(i, j));
            }
        }
        return Mat2d<data_type>(row, col, result_data);
    }
}


/******* operator *******/

template <class data_type>
Mat2d<data_type> operator + (float num, Mat2d<data_type> tensor) {
    return tensor + num;
}

template <class data_type>
Mat2d<data_type> operator - (float num, Mat2d<data_type> tensor) {
    uint32_t row = tensor.get_row(); 
    uint32_t col = tensor.get_col(); 
    data_type num_data[row * col] = {0, };  
    for (int i = 0; i < (int)row; ++i) {
        for (int j = 0; j < (int)col; ++j) {
            int index = i * col + j;
            num_data[index] = num;
        }
    }
    Mat2d<data_type> num_tensor(row, col, num_data);
    return num_tensor - tensor;
}

template <class data_type>
Mat2d<data_type> operator * (float num, Mat2d<data_type> tensor) {
    return tensor * num;
}

template <class data_type>
Mat2d<data_type> operator / (float num, Mat2d<data_type> tensor) {
    uint32_t row = tensor.get_row(); 
    uint32_t col = tensor.get_col(); 
    data_type num_data[row * col] = {0, };  
    for (int i = 0; i < (int)row; ++i) {
        for (int j = 0; j < (int)col; ++j) {
            int index = i * col + j;
            num_data[index] = num;
        }
    }
    Mat2d<data_type> num_tensor(row, col, num_data);
    return num_tensor / tensor;
}

#endif //_MAT2D_H_
