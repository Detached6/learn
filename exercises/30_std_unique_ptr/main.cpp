#include "../exercise.h"
#include <memory>
#include <string>
#include <vector>
#include <cstring>
#include <cassert>

// READ: `std::unique_ptr` <https://zh.cppreference.com/w/cpp/memory/unique_ptr>

std::vector<std::string> RECORDS;

class Resource {
    std::string _records;

public:
    void record(char record) {
        _records.push_back(record);
    }

    ~Resource() {
        RECORDS.push_back(_records);
    }
};

using Unique = std::unique_ptr<Resource>;
Unique reset(Unique ptr) {
    if (ptr) {
        ptr->record('r');
    }
    return std::make_unique<Resource>();
}
Unique drop(Unique ptr) {
    if (ptr) {
        ptr->record('d');
    }
    return nullptr;
}
Unique forward(Unique ptr) {
    if (ptr) {
        ptr->record('f');
    }
    return ptr;
}

int main(int argc, char **argv) {
    std::vector<std::string> problems[3];

    // 处理问题1
    drop(forward(reset(nullptr)));
    std::cout << "Before assignment (problem 1), RECORDS size: " << RECORDS.size() << std::endl;  // 调试输出，查看此时RECORDS元素个数
    problems[0] = RECORDS;
    RECORDS.clear();  // 清空RECORDS，以便下一步

    // 处理问题2
    forward(drop(reset(forward(forward(reset(nullptr))))));
    std::cout << "Before assignment (problem 2), RECORDS size: " << RECORDS.size() << std::endl;  // 调试输出
    problems[1] = RECORDS;
    RECORDS.clear();  // 清空RECORDS，以便下一步

    // 处理问题3
    drop(drop(reset(drop(reset(reset(nullptr))))));
    std::cout << "Before assignment (problem 3), RECORDS size: " << RECORDS.size() << std::endl;  // 调试输出
    problems[2] = RECORDS;
    RECORDS.clear();  // 清空RECORDS，以便下一步

    // ---- 不要修改以上代码 ----

    std::vector<const char *> answers[] = {
        {"fd"},
        {"f", "f", "r", "d", "f"},
        {"r", "d", "r", "d", "r", "d"}
    };

    // ---- 不要修改以下代码 ----

    for (int i = 0; i < 3; ++i) {
        assert(problems[i].size() == answers[i].size() && "wrong size");
        for (int j = 0; j < problems[i].size(); ++j) {
            assert(std::strcmp(problems[i][j].c_str(), answers[i][j]) == 0 && "wrong location");
        }
    }

    return 0;
}