#include "../exercise.h"
#include <numeric>

// READ: `std::accumulate` <https://zh.cppreference.com/w/cpp/algorithm/accumulate>

int main(int argc, char **argv) {
    using DataType = float;
    int shape[]{1, 3, 224, 224};

    // 计算张量的总元素数量
    int total_elements = std::accumulate(std::begin(shape), std::end(shape), 1, std::multiplies<int>());

    // 数据类型为 float，每个元素占 4 字节
    int size = total_elements * sizeof(DataType);

    ASSERT(size == 602112, "4x1x3x224x224 = 602112");

    return 0;
}
