#include "../algo.h"

#include <vector>

int test() {
    int err = 0;

    std::vector<std::vector<int>> nums = {{1, 2, 3, 4, 5}, {0}, {}, {256, 256}};
    std::vector<int> etalon = {15, 0, 0, 512};
    std::vector<int> ans{};

    ans.reserve(nums.size());
    for (const auto & i : nums) {
        ans.push_back(vector_sum(i));
    }

    for (size_t i = 0; i < etalon.size(); ++i) {
        if (ans[i] != etalon[i]) {
            ++err;
        }
    }

    return err;
}

int main () {
    int err = 0;

    err += test();

    return err;
}