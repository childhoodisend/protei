//
// Created by pahpan on 10/13/21.
//

#ifndef PROTEI_ALGO_H
#define PROTEI_ALGO_H

#pragma once

#include <vector>
#include <string>
#include <algorithm>

/**
 *
 * @param num_vec
 * @return sum of nums in vector num_vec
 */
int vector_sum(const std::vector<int>& num_vec) noexcept {

    int sum = 0;

    for(auto &num : num_vec) {

        std::cout << "num " << num << std::endl;

        sum += num;
    }


    return sum;
}

/**
 *
 * @param s
 * @return true if s is num
 */
bool is_number(const std::string& s) {

    auto it = s.begin();
    while(it != s.end() && std::isdigit(*it)) {
        ++it;
    }

    return !s.empty() && it == s.end();
}

/**
 *
 * @param str
 * @return vector of nums in str
 */
std::vector<int> get_nums_from_str(const std::string& str) {

    std::vector<int> nums{};
    nums.reserve(str.length() / 2);
    std::string delim = " ";
    std::string str_mod = str[str.length()] == ' ' ? str : str + ' ';

    str_mod.erase(std::remove(str_mod.begin(), str_mod.end(), ','), str_mod.end());

    auto start = 0U;
    auto end = str_mod.find(delim);
    while (end != std::string::npos) {
        std::string cur_str = str_mod.substr(start, end - start);

        if (is_number(cur_str)) {
            int num = std::stoi(cur_str);
            nums.push_back(num);
        }

        start = end + delim.length();
        end = str_mod.find(delim, start);
    }

    return nums;
}


#endif //PROTEI_ALGO_H
