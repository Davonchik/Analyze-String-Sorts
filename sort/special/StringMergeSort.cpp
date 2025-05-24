#include "StringMergeSort.h"

#include <algorithm>

struct StrWithLcp {
    StrWithLcp() = default;
    StrWithLcp(StrWithLcp&&) = default;
    StrWithLcp& operator=(StrWithLcp&&) = default; 
    std::string str;
    int lcp;
};

inline std::pair<char, int> LcpCompare(const std::string& first, const std::string& second, int k, size_t& cnt) {
    const int n = first.size();
    const int m = second.size();
    int i = k;
    const int min_len = std::min(n, m);
    while (i < min_len && first[i] == second[i]) {
        ++cnt;
        ++i;
    }
    
    if (i < min_len) {
        ++cnt;
        return {first[i] < second[i] ? '<' : '>', i};
    }
    
    return {n == m ? '=' : (n < m ? '<' : '>'), i};
}

size_t StringMerge(std::vector<StrWithLcp>& array, int l1, int r1, int l2, int r2, std::vector<StrWithLcp>& buffer) {
    int i = l1;
    int j = l2;
    int dst = 0;

    size_t cnt = 0;
    while (i < r1 && j < r2) {
        if (array[i].lcp > array[j].lcp) {
            buffer[dst++] = std::move(array[i++]);
        } else if (array[i].lcp < array[j].lcp) {
            buffer[dst++] = std::move(array[j++]);
        } else {
            
            auto [res, lcp] = LcpCompare(array[i].str, array[j].str, array[i].lcp, cnt);

            if (res == '<') {
                buffer[dst++] = std::move(array[i++]);
                array[j].lcp = lcp;
            } else {
                buffer[dst++] = std::move(array[j++]);
                array[i].lcp = lcp;
            }
        }
    }
    while (i < r1) {
        buffer[dst++] = std::move(array[i++]);
    }
    while (j < r2) {
        buffer[dst++] = std::move(array[j++]);
    }
    std::move(buffer.begin(), buffer.begin() + dst, array.begin() + l1);
    return cnt;
}

size_t StringMergeSort(s_iterator begin, s_iterator end) {
    std::vector<StrWithLcp> extended;
    extended.reserve(end - begin);
    for (auto it = begin; it < end; ++it) {
        StrWithLcp element;
        element.lcp = 0;
        element.str = std::move(*it);
        extended.emplace_back(std::move(element));
    }
    size_t cnt = 0;
    std::vector<StrWithLcp> buffer(end - begin);
    int size = end - begin;
    for (int len = 1; len < size; len *= 2) {
        for (int i = 0; i < size; i += 2 * len) {
            int mid = std::min(i + len, size);
            int r2 = std::min(i + 2 * len, size);
            cnt += StringMerge(extended, i, mid, mid, r2, buffer);
        }
    }
    
    for (int i = 0; i < size; ++i) {
        *(begin++) = std::move(extended[i].str);
    }
    return cnt;
}
