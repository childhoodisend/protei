#include "../algo.h"

#include <string>
#include <vector>

int test() {
    int err = 0;

    std::vector<std::string> str = {"1 apple, 2 oranges", "1 2 3 4 5", " ", "300 $"};
    std::vector<std::vector<int>> etalon = {{1, 2}, {1, 2, 3, 4, 5}, {}, {300}};
    std::vector<std::vector<int>> nums{{}, {}, {}, {}};

    for (size_t i = 0; i < str.size(); ++i) {
        nums[i] = get_nums_from_str(str[i]);
    }

    for (size_t i = 0; i < etalon.size(); ++i) {
        for (size_t j = 0; j < etalon[i].size(); ++j) {
            if (etalon[i][j] != nums[i][j]) {
                ++err;
            }
        }
    }

    return err;
}

int main () {
    int err = 0;

    err += test();

    return err;
}
