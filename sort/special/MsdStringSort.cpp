
#include "MsdStringSort.h"

#include "internal/MsdStringSorter.h"

size_t MsdStringSort(s_iterator begin, s_iterator end) {
    return MsdStringSorter(begin, end).Sort<false>();
}
