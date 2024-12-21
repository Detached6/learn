﻿#include "../exercise.h"
#include <algorithm>
#include <string>
#include <vector>

// READ: `std::transform` <https://zh.cppreference.com/w/cpp/algorithm/transform>
// READ: `std::vector::begin` <https://zh.cppreference.com/w/cpp/container/vector/begin>

int main(int argc, char **argv) {
    std::vector<int> val{8, 13, 21, 34, 55};
    std::vector<std::string> ans(val.size());  // 确保 ans 有足够的空间存储结果

    // 使用 std::transform，将每个元素乘以 2，并转为字符串
    std::transform(val.begin(), val.end(), ans.begin(), [](int n) {
        return std::to_string(n * 2);  // 乘以 2 后转为字符串
    });

    // 验证答案
    ASSERT(ans.size() == val.size(), "ans size should be equal to val size");
    ASSERT(ans[0] == "16", "ans[0] should be 16");
    ASSERT(ans[1] == "26", "ans[1] should be 26");
    ASSERT(ans[2] == "42", "ans[2] should be 42");
    ASSERT(ans[3] == "68", "ans[3] should be 68");
    ASSERT(ans[4] == "110", "ans[4] should be 110");

    return 0;
}
