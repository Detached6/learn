#include "../exercise.h"
#include <memory>
#include <cassert>

// READ: `std::shared_ptr` <https://zh.cppreference.com/w/cpp/memory/shared_ptr>
// READ: `std::weak_ptr` <https://zh.cppreference.com/w/cpp/memory/weak_ptr>

// TODO: 将下列 `?` 替换为正确的值
int main(int argc, char **argv) {
    auto shared = std::make_shared<int>(10);
    std::shared_ptr<int> ptrs[]{shared, shared, shared};

    std::weak_ptr<int> observer = shared;
    assert(observer.use_count() == 3 && "Initial use_count check");

    ptrs[0].reset();
    assert(observer.use_count() == 2 && "After ptrs[0].reset()");

    ptrs[1] = nullptr;
    assert(observer.use_count() == 1 && "After ptrs[1] = nullptr");

    ptrs[2] = std::make_shared<int>(*shared);
    assert(observer.use_count() == 1 && "After ptrs[2] = std::make_shared<int>(*shared)");

    ptrs[0] = shared;
    ptrs[1] = shared;
    ptrs[2] = std::move(shared);
    assert(observer.use_count() == 3 && "After reassigning ptrs array");

    std::ignore = std::move(ptrs[0]);
    ptrs[1] = std::move(ptrs[1]);
    ptrs[1] = std::move(ptrs[2]);
    assert(observer.use_count() == 3 && "After multiple std::move operations on ptrs");

    shared = observer.lock();
    assert(observer.use_count() == 4 && "After shared = observer.lock()");

    shared = nullptr;
    for (auto &ptr : ptrs) ptr = nullptr;
    assert(observer.use_count() == 0 && "After setting shared and ptrs to nullptr");

    shared = observer.lock();
    assert(observer.use_count() == 0 && "After another shared = observer.lock()");

    return 0;
}