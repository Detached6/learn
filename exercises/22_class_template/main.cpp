#include <cstring>
#include <iostream>
#include <cassert>
#include <algorithm>

// READ: 类模板 <https://zh.cppreference.com/w/cpp/language/class_template>

template<class T>
struct Tensor4D {
    unsigned int shape[4];
    T *data;

    Tensor4D(unsigned int const shape_[4], T const *data_) {
        unsigned int size = 1;
        // 使用std::copy解决类型不兼容的赋值问题，将传入的形状信息复制到shape数组
        std::copy(shape_, shape_ + 4, shape);
        for (unsigned int i = 0; i < 4; ++i) {
            size *= shape[i];
        }
        data = new T[size];
        std::memcpy(data, data_, size * sizeof(T));
    }
    ~Tensor4D() {
        delete[] data;
    }

    // 为了保持简单，禁止复制和移动
    Tensor4D(Tensor4D const &) = delete;
    Tensor4D(Tensor4D &&) noexcept = delete;

    // 这个加法需要支持“单向广播”。
    // 具体来说，`others` 可以具有与 `this` 不同的形状，形状不同的维度长度必须为1。
    // `others` 长度为1但 `this` 长度不为1的维度将发生广播计算。
    // 例如，`this` 形状为 `[1, 2, 3, 4]`，`others` 形状为 `[1, 2, 1, 4]`，
    // 则 `this` 与 `others` 相加时，3个形状为 `[1, 2, 1, 4]` 的子张量各自与 `others` 对应项相加。
    Tensor4D<T> &operator+=(Tensor4D const &others) {
        // 获取当前张量（this）和传入张量（others）的各维度大小
        unsigned int thisShape[4];
        unsigned int otherShape[4];
        for (unsigned int i = 0; i < 4; ++i) {
            thisShape[i] = shape[i];
            otherShape[i] = others.shape[i];
        }

        // 计算广播后的形状，取每个维度上的较大值作为广播后的维度大小
        unsigned int broadcastShape[4];
        for (unsigned int i = 0; i < 4; ++i) {
            broadcastShape[i] = (thisShape[i] > otherShape[i])? thisShape[i] : otherShape[i];
        }

        // 遍历广播后的形状的每个维度，进行广播和加法操作
        for (unsigned int n = 0; n < broadcastShape[0]; ++n) {
            for (unsigned int c = 0; c < broadcastShape[1]; ++c) {
                for (unsigned int h = 0; h < broadcastShape[2]; ++h) {
                    for (unsigned int w = 0; w < broadcastShape[3]; ++w) {
                        // 计算当前位置在原张量（this）中的索引
                        unsigned int thisIndex = (n * thisShape[1] + c) * thisShape[2] + h;
                        thisIndex = thisIndex * thisShape[3] + w;

                        // 计算当前位置在传入张量（others）中的索引，考虑广播情况（维度大小为1时重复使用对应元素）
                        unsigned int otherIndex = (n < otherShape[0]? n : 0) * otherShape[1] + (c < otherShape[1]? c : 0);
                        otherIndex = otherIndex * otherShape[2] + (h < otherShape[2]? h : 0);
                        otherIndex = otherIndex * otherShape[3] + (w < otherShape[3]? w : 0);

                        // 如果索引在原张量和传入张量的有效范围内，执行加法操作
                        if (n < thisShape[0] && c < thisShape[1] && h < thisShape[2] && w < thisShape[3] &&
                            (n < otherShape[0] || otherShape[0] == 1) &&
                            (c < otherShape[1] || otherShape[1] == 1) &&
                            (h < otherShape[2] || otherShape[2] == 1) &&
                            (w < otherShape[3] || otherShape[3] == 1)) {
                            data[thisIndex] += others.data[otherIndex];
                        }
                    }
                }
            }
        }

        return *this;
    }
};

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    {
        unsigned int shape[]{1, 2, 3, 4};
        // clang-format off
        int data[]{
             1,  2,  3,  4,
             5,  6,  7,  8,
             9, 10, 11, 12,

            13, 14, 15, 16,
            17, 18, 19, 20,
            21, 22, 23, 24};
        // clang-format on
        auto t0 = Tensor4D(shape, data);
        auto t1 = Tensor4D(shape, data);
        t0 += t1;
        for (auto i = 0u; i < sizeof(data) / sizeof(*data); ++i) {
            assert(t0.data[i] == data[i] * 2 && "Tensor doubled by plus its self.");
        }
    }
    {
        unsigned int s0[]{1, 2, 3, 4};
        // clang-format off
        float d0[]{
            1, 1, 1, 1,
            2, 2, 2, 2,
            3, 3, 3, 3,

            4, 4, 4, 4,
            5, 5, 5, 5,
            6, 6, 6, 6};
        // clang-format on
        unsigned int s1[]{1, 2, 3, 1};
        // clang-format off
        float d1[]{
            6,
            5,
            4,

            3,
            2,
            1};
        // clang-format on

        auto t0 = Tensor4D(s0, d0);
        auto t1 = Tensor4D(s1, d1);
        t0 += t1;
        for (auto i = 0u; i < sizeof(d0) / sizeof(*d0); ++i) {
            assert(t0.data[i] == 7.f && "Every element of t0 should be 7 after adding t1 to it.");
        }
    }
    {
        unsigned int s0[]{1, 2, 3, 4};
        // clang-format off
        double d0[]{
             1,  2,  3,  4,
             5,  6,  7,  8,
             9, 10, 11, 12,

            13, 14, 15, 16,
            17, 18, 19, 20,
            21, 22, 23, 24};
        // clang-format on
        unsigned int s1[]{1, 1, 1, 1};
        double d1[]{1};

        auto t0 = Tensor4D(s0, d0);
        auto t1 = Tensor4D(s1, d1);
        t0 += t1;
        for (auto i = 0u; i < sizeof(d0) / sizeof(*d0); ++i) {
            assert(t0.data[i] == d0[i] + 1 && "Every element of t0 should be incremented by 1 after adding t1 to it.");
        }
    }
    return 0;
}