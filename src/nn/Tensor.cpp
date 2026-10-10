//
// Created by marcus on 10/9/26.
//

#include "nn/Tensor.hpp"

#include <stdexcept>

Tensor::Tensor(float data): _data{data}, _shape{}, _stride{} {};
Tensor::Tensor(std::vector<float> data): _data{data}, _shape{data.size()}, _stride{1} {};
Tensor::Tensor(std::vector<std::vector<float>> data):  _shape{data.size(), data.size()}, _stride{data.size(), 1} {
    // checking if dimension match
    std::size_t num_expected_columns = data.size();
    for (std::size_t i = 0; i < num_expected_columns; ++i) {
        if (data[i].size() != num_expected_columns) {
            throw std::invalid_argument("Dimensions do not match");
        }
    }
    // store in row major format to more efficient use in cache
    for (std::size_t i = 0; i < data.size(); ++i) {
        for (std::size_t j = 0; j < data[i].size(); ++j) {
            _data.push_back(data[i][j]);
        }
    }
};

// works only with scalars and 1dim tensors
const float &Tensor::item() const {
    if (_data.size() == 1) {
        return _data[0];
    }
    throw std::runtime_error("Item() can only be called on Tensor");
}

const float& Tensor::operator()(std::size_t index) const {
    if (_shape.size() == 0) {
        throw std::invalid_argument("Shape cannot be 0.");
    }

    if (_shape.size() == 1) {
        if (index >= _shape[0]) {
            throw std::out_of_range("Index out of range");
        }
        return _data[index];
    }
    throw std::invalid_argument("Index out of range");
}
