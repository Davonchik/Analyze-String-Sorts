#include "MergeSort.h"
#include "cmp.h"

// --------------------------- merge ----------------------------
void merge(std::vector<std::string>& a,
           int left, int mid, int right,
           std::vector<std::string>& buffer, size_t& cmpCount) {
    int i = left;      // текущий индекс левой половины
    int j = mid + 1;   // текущий индекс правой половины
    int k = left;      // позиция для записи в buffer

    // Слияние двух отсортированных половин
    while (i <= mid && j <= right) {
        if (IsLess(a[i], a[j], cmpCount))
            buffer[k++] = std::move(a[i++]);
        else
            buffer[k++] = std::move(a[j++]);
    }

    // Дозаписываем «хвост»
    while (i <= mid)  buffer[k++] = std::move(a[i++]);
    while (j <= right) buffer[k++] = std::move(a[j++]);

    // Копируем результат обратно в исходный вектор
    for (int t = left; t <= right; ++t)
        a[t] = std::move(buffer[t]);
}

// ------------------------- mergeSort -------------------------
size_t mergeSort(std::vector<std::string>& a,
               int left, int right,
               std::vector<std::string>& buffer) {
    if (left >= right) return 0;            // 0–1 элемент — уже отсортировано

    int mid = left + (right - left) / 2;
    size_t cnt = 0;
    cnt += mergeSort(a, left, mid, buffer);      // сортируем левую половину
    cnt += mergeSort(a, mid + 1, right, buffer); // сортируем правую половину
    merge(a, left, mid, right, buffer, cnt);   // сливаем
    return cnt;
}

// Удобная «обёртка» для пользователя
size_t mergeSort(std::vector<std::string>& a) {
    if (a.empty()) return 0;
    std::vector<std::string> buffer(a.size());
    return mergeSort(a, 0, static_cast<int>(a.size()) - 1, buffer);
}
