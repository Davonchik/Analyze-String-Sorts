#include "QuickSort.h"
#include "cmp.h"
#include <utility>  // std::swap
#include <algorithm>

using s_iterator = std::vector<std::string>::iterator;

static s_iterator med3(s_iterator from, s_iterator to, size_t& cmp) {
    s_iterator strs[] = {from, (to - 1), (from + (to - from) / 2)};
    if (IsLess(*strs[1], *strs[0], cmp)) {
        std::swap(strs[1], strs[0]);
    }
    if (IsLess(*strs[2], *strs[0], cmp)) {
        std::swap(strs[2], strs[0]);
    }
    if (IsLess(*strs[2], *strs[1], cmp)) {
        return strs[2];
    }
    return strs[1];
}

// ------------------------- quickSort -------------------------
size_t quickSort(std::vector<std::string>::iterator begin, std::vector<std::string>::iterator end) {
    
    if (end - begin <= 1)
        return 0;

    size_t comparsions = 0;

    auto pivot_it = med3(begin, end, comparsions);
    auto pivot = *pivot_it;

    std::iter_swap(pivot_it, end - 1);

    auto middle = std::partition(begin, end - 1, [&](const auto& elem)
    {
        return IsLess(elem, pivot, comparsions);
    });

    std::iter_swap(end - 1, middle);
 
    comparsions += quickSort(begin, middle);
    comparsions += quickSort(middle + 1, end);

    return comparsions;
}


