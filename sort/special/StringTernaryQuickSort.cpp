#include "StringTernaryQuickSort.h"

using s_iterator = std::vector<std::string>::iterator;

char inline get(s_iterator from, int len) {
    return (*from)[len];
}

static char med3(s_iterator from, s_iterator to, int len, size_t& cmp) {
    char chars[] = {get(from, len), get(from + (to - from) / 2, len), get(to - 1, len)};
    if (chars[1] < chars[0]) {
        std::swap(chars[1], chars[0]);
        ++cmp;
    }
    if (chars[2] < chars[0]) {
        std::swap(chars[2], chars[0]);
        ++cmp;
    }
    if (chars[2] < chars[1]) {
        ++cmp;
        return chars[2];
    }
    return chars[1];
}

std::pair<s_iterator, s_iterator> TernaryPartition(s_iterator from, s_iterator to, int len, size_t& cmp) {
    if (from == to) return {from, to};
    
    char pivot = med3(from, to, len, cmp);
    
    s_iterator i = from;
    s_iterator j = from;
    s_iterator k = to;
    
    while (j < k) {
        if ((*j)[len] < pivot) {
            std::iter_swap(i, j);
            ++i;
            ++j;
            ++cmp;
        } else if ((*j)[len] == pivot) {
            ++j;
            ++cmp;
        } else {
            --k;
            std::iter_swap(j, k);
        }
    }
    
    return {i, j};
}

size_t StringTernaryQuickSort(s_iterator from, s_iterator to, int len) {
    if (from >= to) [[unlikely]] {
        return 0;
    }

    from = std::partition(from, to, [&](const auto& str) {
        return str.length() < len;
    });

    if (from >= to) [[unlikely]] {
        return 0;
    }

    size_t cmp = 0;
    auto [from_eq, to_eq] = TernaryPartition(from, to, len, cmp);

    cmp += StringTernaryQuickSort(from, from_eq, len);
    cmp += StringTernaryQuickSort(from_eq, to_eq, len + 1);
    cmp += StringTernaryQuickSort(to_eq, to, len);

    return cmp;
}

size_t StringTernaryQuickSort(s_iterator from, s_iterator to) {
    return StringTernaryQuickSort(from, to, 0);
}



char inline getChecked(s_iterator a, int i, int len) {
    if (len < a[i].length()) {
        return a[i][len];
    }
    return '\0';
}

char inline getChecked(s_iterator s, int len) {
    if (len < s->length()) {
        return (*s)[len];
    }
    return '\0';
}

static s_iterator med3It(s_iterator from, s_iterator to, int len, size_t& cmp) {
    s_iterator chars[] = {from, from + (to - from) / 2, to - 1};
    if (getChecked(chars[1], len) < getChecked(chars[0], len)) {
        std::swap(chars[1], chars[0]);
        ++cmp;
    }
    if (getChecked(chars[2], len) < getChecked(chars[0], len)) {
        std::swap(chars[2], chars[0]);
        ++cmp;
    }
    if (getChecked(chars[2], len) < getChecked(chars[1], len)) {
        ++cmp;
        return chars[2];
    }
    return chars[1];
}

size_t StringTernaryQuickSortPrinceton(s_iterator a, int lo, int hi, int d) {
    if (hi - lo <= 0) {
        return 0;
    }

    size_t comparsions = 0;

    int i = lo - 1;
    int j = hi;
    int p = lo - 1, q = hi;
    auto v_it = med3It(a + lo, a + hi + 1, d, comparsions);
    std::iter_swap(v_it, a + hi);
    char v = getChecked(a, hi, d);

    while (i < j) {
        while (getChecked(a, ++i, d) < v) ++comparsions;
        while (v < getChecked(a, --j, d)) {
            ++comparsions;
            if (j == lo) {
                break;
            }
        }
        if (i > j) break;
        std::swap(a[i], a[j]);
        if (getChecked(a, i, d) == v) { p++; std::swap(a[p], a[i]); }
        if (getChecked(a, j, d) == v) { q--; std::swap(a[j], a[q]); }
    } 
    if (p == q) {
        if (v != '\0') StringTernaryQuickSortPrinceton(a, lo, hi, d + 1);
        return 0;    
    }

    if (getChecked(a, i, d) < v) ++comparsions, i++;

    for (int k = lo; k <= p; k++, j--) std::swap(a[k], a[j]);
    for (int k = hi; k >= q; k--, i++) std::swap(a[k], a[i]);
    comparsions += StringTernaryQuickSortPrinceton(a, lo, j, d);
    if ((i == hi) && (getChecked(a, i, d) == v)) ++comparsions, i++;
    if (v != '\0') comparsions += StringTernaryQuickSortPrinceton(a, j + 1, i - 1, d + 1);
    comparsions += StringTernaryQuickSortPrinceton(a, i, hi, d);   
    return comparsions;
}
