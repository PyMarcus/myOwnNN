#include <iostream>
#include <vector>

#include "nn/Tensor.hpp"

int main() {
    std::vector<float> v{1.0, 2.0, 3.0};
    Tensor tensor(v);

    std::vector<std::vector<float>> v2dim{{1.0, 2.0, 3.0}, {1.0, 2.0, 3.0}, {1.0, 2.0, 3.0}};

    Tensor tensor2dim(v2dim);
    std::cout << tensor << std::endl;
    std::cout << tensor2dim << std::endl;
    return 0;
}
