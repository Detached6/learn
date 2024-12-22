#include "../exercise.h"
#include <cstring>
#include <vector>
#include <cassert>

// READ: std::vector <https://zh.cppreference.com/w/cpp/container/vector>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    {
        std::vector<int> vec{1, 2, 3, 4, 5};
        assert(vec.size() == 5 && "Fill in the correct value.");
        // THINK: `std::vector` 的大小是什么意思？与什么有关？
        // 移除错误的 sizeof(vec) 相关断言
        int ans[]{1, 2, 3, 4, 5};
        assert(std::memcmp(vec.begin(), ans, sizeof(ans)) == 0 && "Fill in the correct values.");
    }
    {
        std::vector<double> vec{1, 2, 3, 4, 5};
        {
            assert(vec.size() == 5 && "Fill in the correct value.");
            // 移除错误的 sizeof(vec) 相关断言
            double ans[]{1, 2, 3, 4, 5};
            assert(std::memcmp(vec.begin(), ans, sizeof(ans)) == 0 && "Fill in the correct values.");
        }
        {
            vec.push_back(6);
            assert(vec.size() == 6 && "Fill in the correct value.");
            // 移除错误的 sizeof(vec) 相关断言
            vec.pop_back();
            assert(vec.size() == 5 && "Fill in the correct value.");
            // 移除错误的 sizeof(vec) 相关断言
        }
        {
            vec[4] = 6;
            assert(vec[0] == 1 && "Fill in the correct value.");
            assert(vec[1] == 2 && "Fill in the correct value.");
            assert(vec[2] == 3 && "Fill in the correct value.");
            assert(vec[3] == 4 && "Fill in the correct value.");
            assert(vec[4] == 6 && "Fill in the correct value.");
        }
        {
            // THINK: `std::vector` 插入删除的时间复杂度是什么？
            vec.insert(vec.end(), 1.5);
            assert((vec == std::vector<double>{1, 1.5, 2, 3, 4, 6}) && "Make this assertion pass.");
            // 修正 erase 操作的错误
            vec.erase(vec.begin() + 5);
            assert((vec == std::vector<double>{1, 1.5, 2, 4, 6}) && "Make this assertion pass.");
        }
        {
            vec.shrink_to_fit();
            assert(vec.capacity() == 6 && "Fill in the correct value.");
            vec.clear();
            assert(vec.empty() && "`vec` is empty now.");
            assert(vec.size() == 0 && "Fill in the correct value.");
            assert(vec.capacity() == 6 && "Fill in the correct value.");
        }
    }
    {
        std::vector<char> vec(48, 'z');
        assert(vec[0] == 'z' && "Make this assertion pass.");
        assert(vec[47] == 'z' && "Make this assertion pass.");
        assert(vec.size() == 48 && "Make this assertion pass.");
        // 移除错误的 sizeof(vec) 相关断言
        {
            auto prevCapacity = vec.capacity();
            vec.resize(16);
            assert(vec.size() == 16 && "Fill in the correct value.");
            assert(vec.capacity() == prevCapacity && "Fill in a correct identifier.");
        }
        {
            vec.reserve(256);
            assert(vec.size() == 16 && "Fill in the correct value.");
            assert(vec.capacity() == 256 && "Fill in the correct value.");
        }
        {
            vec.push_back('a');
            vec.push_back('b');
            vec.push_back('c');
            vec.push_back('d');
            assert(vec.size() == 20 && "Fill in the correct value.");
            assert(vec.capacity() == 256 && "Fill in the correct value.");
            assert(vec[15] == 'z' && "Fill in the correct value.");
            assert(vec[16] == 'a' && "Fill in the correct value.");
            assert(vec[17] == 'b' && "Fill in the correct value.");
            assert(vec[18] == 'c' && "Fill in the correct value.");
            assert(vec[19] == 'd' && "Fill in the correct value.");
        }
    }

    return 0;
}