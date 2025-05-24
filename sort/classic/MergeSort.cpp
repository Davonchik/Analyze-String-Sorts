#include "MergeSort.h"
#include "cmp.h"

void merge(std::vector<std::string>& a,
           int left, int mid, int right,
           std::vector<std::string>& buffer, size_t& cmpCount) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (IsLess(a[i], a[j], cmpCount))
            buffer[k++] = std::move(a[i++]);
        else
            buffer[k++] = std::move(a[j++]);
    }

    while (i <= mid)  buffer[k++] = std::move(a[i++]);
    while (j <= right) buffer[k++] = std::move(a[j++]);

    for (int t = left; t <= right; ++t)
        a[t] = std::move(buffer[t]);
}

size_t mergeSort(std::vector<std::string>& a,
               int left, int right,
               std::vector<std::string>& buffer) {
    if (left >= right) return 0;

    int mid = left + (right - left) / 2;
    size_t cnt = 0;
    cnt += mergeSort(a, left, mid, buffer);
    cnt += mergeSort(a, mid + 1, right, buffer);
    merge(a, left, mid, right, buffer, cnt);
    return cnt;
}

size_t mergeSort(std::vector<std::string>& a) {
    if (a.empty()) return 0;
    std::vector<std::string> buffer(a.size());
    return mergeSort(a, 0, static_cast<int>(a.size()) - 1, buffer);
}
