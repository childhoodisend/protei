#include "../algo.h"

#include <vector>

int test() {
    int err = 0;

    std::vector<std::string> str = {"1", "orange", " ", "$300$"};
    std::vector<bool> etalon = {true, false, false, false};
    std::vector<bool> ans{};

    ans.reserve(str.size());
    for (const auto & i : str) {
        ans.push_back(is_number(i));
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
