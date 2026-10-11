#pragma once

#include <iosfwd>
#include <vector>

class Tensor {
private:
    std::vector<float> _data;
    std::vector<std::size_t> _shape;
    std::vector<std::size_t> _stride;
public:
    Tensor(float data);
    Tensor(std::vector<float> data);
    Tensor(std::vector<std::vector<float>> data);

    const float& item() const;
    float& item();

    const float& operator()(std::size_t index) const;
    float& operator()(std::size_t index);
    const float& operator()(std::size_t i, std::size_t j) const;
    float& operator()(std::size_t index, std::size_t j);
    friend std::ostream& operator<<(std::ostream& out, const Tensor& tensor);

    [[nodiscard]] const std::vector<std::size_t>&shape() const;
    [[nodiscard]] const std::vector<std::size_t>&stride() const;
};