#include "MsdQuickStringSort.h"

#include "internal/MsdStringSorter.h"

size_t MsdQuickStringSort(s_iterator begin, s_iterator end) {
    return MsdStringSorter(begin, end).Sort<true>();
}

