#include "Mat2d.hpp"

Mat2d::Mat2d() {
    this->row = 0;
    this->col = 0;
    this->data = nullptr;
}

Mat2d::Mat2d(uint32_t row, uint32_t col, float* data) {
    //std::cout << "hello" << std::endl;
    this->row = row;
    this->col = col;
    this->data = new float[row * col];
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

Mat2d::~Mat2d() {
    if (data != nullptr)
        delete data;
}

Mat2d::Mat2d(const Mat2d& other) {
    //std::cout << "hello" << std::endl;
    this->row = other.row;
    this->col = other.col;
    this->data = new float[row * col];
    for (int i = 0; i < (int)row; ++i) {
        for (int j = 0; j < (int)col; ++j) {
            int index = (int)col * i + j;
            this->data[index] = other.data[index];
        }
    }
}

Mat2d& Mat2d::operator = (const Mat2d& other) {
        if (row != other.row || col != other.col) {
            row = other.row;
            col = other.col;
            if (data != nullptr) delete data; 
            data = new float[row * col];
        }
	for (int i = 0; i < (int)row; ++i) {
		for (int j = 0; j < (int)col; ++j) {
			int index = i * col + j;
			data[index] = other.data[index];
		}
	}
	return *this;
}

uint32_t Mat2d::get_row() { 
    return this->row;
}
uint32_t Mat2d::get_col() {
    return this->col;
}


Mat2d Mat2d::operator - () {
    float result_data[row * col] = {0,};
    for (int i = 0; i < (int)row; ++i) {
        for (int j = 0; j < (int)col; ++j) {
            int index = i * col + j;
            result_data[index] = -data[index];
        }
    }
    return Mat2d(row, col, result_data);
}

float& Mat2d::operator () (uint32_t row, uint32_t col) {
    assert (row < this->row && col < this->col);
    return data[row * this->col + col];	
}

Mat2d Mat2d::operator [] (const Mat2d& other) {
    assert (row == other.row && col == other.col);
	float result_data[row * col] = {0,};
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
	return Mat2d(row, col, result_data);
}

Mat2d Mat2d::operator + (const Mat2d& other) {
    assert ((row == other.row && col == other.col) or\
            (row == other.row && other.col == 1) or\
            (col == other.col && other.row == 1));
    float result_data[row * col] = {0,};
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
    return Mat2d(row, col, result_data);
}


Mat2d Mat2d::operator - (const Mat2d& other) {
    assert ((row == other.row && col == other.col) or\
            (row == other.row && other.col == 1) or\
            (col == other.col && other.row == 1));
    float result_data[row * col] = {0,};
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
    return Mat2d(row, col, result_data);
}


Mat2d Mat2d::operator * (const Mat2d& other) {
    assert ((row == other.row && col == other.col) or\
            (row == other.row && other.col == 1) or\
            (col == other.col && other.row == 1));
    float result_data[row * col] = {0,};
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
    return Mat2d(row, col, result_data);
}


Mat2d Mat2d::operator / (const Mat2d& other) {
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

    float result_data[row * col] = {0,};
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
    return Mat2d(row, col, result_data);
}




Mat2d Mat2d::operator < (const Mat2d& other) {	
    assert (row == other.row && col == other.col);
    float result_data[row * col] = {0,};
    //float* result_data = new float[row * col];
    for (int i = 0; i < (int)row; ++i) {
        for (int j = 0; j < (int)col; ++j) {
            int index = i * col + j;
            result_data[index] =\
                    (data[index] < other.data[index]) ? 1.0 : 0.0;
            }
    }
    return Mat2d(row, col, result_data);
}

Mat2d Mat2d::operator <= (const Mat2d& other) {
	assert (row == other.row && col == other.col);
	float result_data[row * col] = {0,};
	//float* result_data = new float[row * col];
	for (int i = 0; i < (int)row; ++i) {
		for (int j = 0; j < (int)col; ++j) {
			int index = i * col + j;
			result_data[index] =\
				(data[index] <= other.data[index]) ? 1.0 : 0.0;
		}
	}
	return Mat2d(row, col, result_data);
}

Mat2d Mat2d::operator > (const Mat2d& other) {
	assert (row == other.row && col == other.col);
	float result_data[row * col] = {0,};
	//float* result_data = new float[row * col];
	for (int i = 0; i < (int)row; ++i) {
		for (int j = 0; j < (int)col; ++j) {
			int index = i * col + j;
			result_data[index] =\
				(data[index] > other.data[index]) ? 1.0 : 0.0;
		}
	}
	return Mat2d(row, col, result_data);
}
Mat2d Mat2d::operator >= (const Mat2d& other) {
	assert (row == other.row && col == other.col);
	float result_data[row * col] = {0,};
	//float* result_data = new float[row * col];
	for (int i = 0; i < (int)row; ++i) {
		for (int j = 0; j < (int)col; ++j) {
			int index = i * col + j;
			result_data[index] =\
				(data[index] >= other.data[index]) ? 1.0 : 0.0;
		}
	}
	return Mat2d(row, col, result_data);
}

Mat2d Mat2d::operator == (const Mat2d& other) {
	assert (row == other.row && col == other.col);
	float result_data[row * col] = {0,};
	for (int i = 0; i < (int)row; ++i) {
		for (int j = 0; j < (int)col; ++j) {
			int index = i * col + j;
			result_data[index] =\
				(data[index] == other.data[index]) ? 1.0 : 0.0;
		}
	}
	return Mat2d(row, col, result_data);
}

Mat2d Mat2d::operator != (const Mat2d& other) {
	assert (row == other.row && col == other.col);
	float result_data[row * col] = {0,};
	//float* result_data = new float[row * col];
	for (int i = 0; i < (int)row; ++i) {
		for (int j = 0; j < (int)col; ++j) {
			int index = i * col + j;
			result_data[index] =\
				(data[index] != other.data[index]) ? 1.0 : 0.0;
		}
	}
	return Mat2d(row, col, result_data);
}


Mat2d Mat2d::operator + (float num) {

    float result_data[row * col] = {0,};
    for (int i = 0; i < (int)row; ++i) {
        for (int j = 0; j < (int)col; ++j) {
            int index = i * col + j;
            result_data[index] = data[index] + num;
        }
    }
    return Mat2d(row, col, result_data);
}


Mat2d Mat2d::operator - (float num) {

    float result_data[row * col] = {0,};
    for (int i = 0; i < (int)row; ++i) {
        for (int j = 0; j < (int)col; ++j) {
            int index = i * col + j;
            result_data[index] = data[index] - num;
        }
    }
    return Mat2d(row, col, result_data);
}


Mat2d Mat2d::operator * (float num) {
    float result_data[row * col] = {0,};
    for (int i = 0; i < (int)row; ++i) {
        for (int j = 0; j < (int)col; ++j) {
            int index = i * col + j;
            result_data[index] = data[index] * num;
        }
    }
    return Mat2d(row, col, result_data);
}


Mat2d Mat2d::operator / (float num) {

    assert (num != 0);

    float result_data[row * col] = {0,};
    for (int i = 0; i < (int)row; ++i) {
        for (int j = 0; j < (int)col; ++j) {
            int index = i * col + j;
            result_data[index] = data[index] / num;
        }
    }
    return Mat2d(row, col, result_data);
}

Mat2d Mat2d::operator < (float num) {
	float result_data[row * col] = {0,};
	for (int i = 0; i < (int)row; ++i) {
		for (int j = 0; j < (int)col; ++j) {
			int index = i * col + j;
			result_data[index] = (data[index] < num) ? 1.0 : 0.0;
		}
	}
	return Mat2d(row, col, result_data);
}

Mat2d Mat2d::operator <= (float num) {
	float result_data[row * col] = {0,};
	for (int i = 0; i < (int)row; ++i) {
		for (int j = 0; j < (int)col; ++j) {
			int index = i * col + j;
			result_data[index] = (data[index] <= num) ? 1.0 : 0.0;
		}
	}
	return Mat2d(row, col, result_data);
}

Mat2d Mat2d::operator > (float num) {
	float result_data[row * col] = {0,};
	for (int i = 0; i < (int)row; ++i) {
		for (int j = 0; j < (int)col; ++j) {
			int index = i * col + j;
			result_data[index] = (data[index] > num) ? 1.0 : 0.0;
		}
	}
	return Mat2d(row, col, result_data);
}

Mat2d Mat2d::operator >= (float num) {
	float result_data[row * col] = {0,};
	for (int i = 0; i < (int)row; ++i) {
		for (int j = 0; j < (int)col; ++j) {
			int index = i * col + j;
			result_data[index] = (data[index] >= num) ? 1.0 : 0.0;
		}
	}
	return Mat2d(row, col, result_data);
}
Mat2d Mat2d::operator == (float num) {
	float result_data[row * col] = {0,};
	for (int i = 0; i < (int)row; ++i) {
		for (int j = 0; j < (int)col; ++j) {
			int index = i * col + j;
			result_data[index] = (data[index] == num) ? 1.0 : 0.0;
		}
	}
	return Mat2d(row, col, result_data);
}
Mat2d Mat2d::operator != (float num) {
	float result_data[row * col] = {0,};
	for (int i = 0; i < (int)row; ++i) {
		for (int j = 0; j < (int)col; ++j) {
			int index = i * col + j;
			result_data[index] = (data[index] != num) ? 1.0 : 0.0;
		}
	}
	return Mat2d(row, col, result_data);
}

Mat2d Mat2d::max() {
    float max_data[1] = {data[0]};
    for (int i = 0; i < (int)row; ++i) {
        for (int j = 0; j < (int)col; ++j) {
            int index = i * col + j;
            max_data[0] = max_data[0] >= data[index] ?\
                            max_data[0] : data[index];

        }
    }
    return Mat2d(1, 1, max_data);
}

Mat2d Mat2d::sum(int axis) {
    //TODO if axis=None, return sum of all elements
    assert (axis == -1 or axis == 0 or axis == 1);

    if (axis == -1) {
        float sum[1] = {0};
        for (int i = 0; i < (int)row; ++i) {
            for (int j = 0; j < (int)col; ++j) {
                sum[0] += data[i * col + j]; 
            }
        }
        return Mat2d(1, 1, sum);
    }

    uint32_t result_dim = (axis == 0) ? col : row;
    float result_data[result_dim] = {0,};
    if (axis == 0) {
        for (int i = 0; i < (int)row; ++i) {
            for (int j = 0; j < (int)col; ++j) {
                result_data[j] += data[i * col + j]; 
            }
        }
        return Mat2d(1, result_dim, result_data);
    }
    else {
        for (int i = 0; i < (int)row; ++i) {
            for (int j = 0; j < (int)col; ++j) {
                result_data[i] += data[i * col + j];
            }
        }
        return Mat2d(result_dim, 1, result_data);
    }
}

Mat2d Mat2d::dot(const Mat2d& other) {
    assert (col == other.row);
    float result_data[row * other.col] = {0,}; 
    for (int i = 0; i < (int)row; ++i) {
        for (int j = 0; j < (int)other.col; ++j) {
            int index = i * other.col + j;
            for (int k = 0; k < (int)col; ++k) {
                result_data[index] +=\
                    data[i * col + k] * other.data[j + k * other.col];
            }
        }
    }
    return Mat2d(row, other.col, result_data);
}

Mat2d Mat2d::T() {
    // TODO : improve for multi dimension
    float result_data[col * row] = {0,};
    for (int i = 0; i < (int)row; ++i) {
        for (int j = 0; j < (int)col; ++j) {
            int cur_index = i * col + j;
            int result_index = j * row + i;
            result_data[result_index] = data[cur_index];
        }
    }
    return Mat2d(col, row, result_data);
}


/* 
 * Mat2d operator 
 *
 */
Mat2d zeros(uint32_t row, uint32_t col) {
    float zero_data[row * col] = {0,};
    return Mat2d(row, col, zero_data);
}
Mat2d operator+(float num, Mat2d tensor) {
    return tensor + num;
}
Mat2d operator-(float num, Mat2d tensor) {
    uint32_t row = tensor.get_row(); 
    uint32_t col = tensor.get_col(); 
    float num_data[row * col] = {0, };  
    for (int i = 0; i < (int)row; ++i) {
        for (int j = 0; j < (int)col; ++j) {
            int index = i * col + j;
            num_data[index] = num;
        }
    }
    Mat2d num_tensor(row, col, num_data);
    return num_tensor - tensor;
}
Mat2d operator*(float num, Mat2d tensor) {
    return tensor * num;
}
Mat2d operator/(float num, Mat2d tensor) {
    uint32_t row = tensor.get_row(); 
    uint32_t col = tensor.get_col(); 
    float num_data[row * col] = {0, };  
    for (int i = 0; i < (int)row; ++i) {
        for (int j = 0; j < (int)col; ++j) {
            int index = i * col + j;
            num_data[index] = num;
        }
    }
    Mat2d num_tensor(row, col, num_data);
    return num_tensor / tensor;
}

Mat2d reverse_boolean(Mat2d tensor) {
    uint32_t row = tensor.get_row(); 
    uint32_t col = tensor.get_col(); 
    float result_data[row * col] = {0,};
    for (int i = 0; i < (int)row; ++i) {
        for (int j = 0; j < (int)col; ++j) {
            int index = i * col + j;
            result_data[index] =\
                    tensor(i, j) == 1 ? 0 : 1;
        }
    }
    return Mat2d(row, col, result_data);
}

Mat2d exp(Mat2d tensor) {
    //TODO how to get reference input.
    uint32_t row = tensor.get_row(); 
    uint32_t col = tensor.get_col(); 
    float result_data[row * col] = {0,};
    for (int i = 0; i < (int)row; ++i) {
        for (int j = 0; j < (int)col; ++j) {
            int index = i * col + j;
            result_data[index] = std::exp(tensor(i, j));
        }
    }
    return Mat2d(row, col, result_data);
}

Mat2d log(Mat2d tensor) {
    uint32_t row = tensor.get_row(); 
    uint32_t col = tensor.get_col(); 
    float result_data[row * col] = {0,};
    for (int i = 0; i < (int)row; ++i) {
        for (int j = 0; j < (int)col; ++j) {
            int index = i * col + j;
            result_data[index] = std::log(tensor(i, j));
        }
    }
    return Mat2d(row, col, result_data);
}
