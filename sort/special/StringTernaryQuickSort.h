#pragma once

#include "StringIterator.h"

size_t StringTernaryQuickSort(s_iterator from, s_iterator to, int len);

size_t StringTernaryQuickSort(s_iterator from, s_iterator to);

// https://www.cs.princeton.edu/courses/archive/fall04/cos226/lectures/radix.4up.pdf
size_t StringTernaryQuickSortPrinceton(s_iterator a, int lo, int hi, int d);