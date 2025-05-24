#pragma once

#include <utility>
#include <string>

static bool IsLess(const std::string& str1, const std::string& str2, size_t& cnt) {
    size_t comparisons = 0;
    size_t min_len = std::min(str1.size(), str2.size());
    
    for (size_t i = 0; i < min_len; ++i) {
        ++comparisons;
        if (str1[i] != str2[i]) {
            cnt += comparisons;
            return str1[i] < str2[i];
        }
    }
    cnt += comparisons;
    return str1.size() < str2.size();
}

static bool IsGreater(const std::string& str1, const std::string& str2, size_t& cnt) {
    int comparisons = 0;
    size_t min_len = std::min(str1.size(), str2.size());

    for (size_t i = 0; i < min_len; ++i) {
        ++comparisons;
        if (str1[i] != str2[i]) {
            cnt += comparisons;
            return str1[i] > str2[i]; 
        }
    }
    cnt += comparisons;
    return str1.size() > str2.size();
}
