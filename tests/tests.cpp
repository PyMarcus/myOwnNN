//
// Created by marcus on 10/9/26.
//

#include "gtest/gtest.h"
#include "nn/Tensor.hpp"

TEST(HelloTest, BasicTest) {
    EXPECT_EQ(1, 1);
}

TEST(TensorTest, PrintsVector) {
    Tensor t(std::vector<float>{1, 2, 3, 4});

    std::ostringstream out;
    out << t;
    EXPECT_EQ(out.str(), "[1, 2, 3, 4]");
};

TEST(TensorTest, PrintsMatrix) {
    Tensor t(std::vector<std::vector<float>>{{1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}});
    std::ostringstream out;
    out << t;
    EXPECT_EQ(out.str(), "[[1, 2, 3, 4], [1, 2, 3, 4], [1, 2, 3, 4], [1, 2, 3, 4]]");
}