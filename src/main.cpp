#include <iostream>
#include <vector>

#include "nn/Tensor.hpp"

int main() {
    std::vector<float> v{1.0, 2.0, 3.0};
    Tensor tensor(v);

    std::cout << tensor << std::endl;
    return 0;
}
