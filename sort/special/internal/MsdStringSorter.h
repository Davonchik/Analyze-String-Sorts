#include "../StringTernaryQuickSort.h"

#include <algorithm>
#include <numeric>

class MsdStringSorter {

public:
    MsdStringSorter(s_iterator begin, s_iterator end) : begin(begin), end(end), buffer(end - begin) {}

    template <bool WithQuickSort = false>
    size_t Sort() {
        return Sort<WithQuickSort>(begin, end, 0);
    }

private:
    template <bool WithQuickSort>
    size_t Sort(s_iterator begin, s_iterator end, int len) {
        if (begin + 1 >= end) {
            return 0;
        }
    
        if constexpr (WithQuickSort) {
            if (std::distance(begin, end) < 74) {
                return StringTernaryQuickSortPrinceton(begin, 0, end - begin - 1, len);
            }
        }
        
        auto get = [&] (std::string& s) -> int {
            return len < s.length() ? static_cast<int>(s[len]) + 128 : 0;
        };
    
        std::vector<int> cnt(257, 0);
        std::vector<int> pref_cnt(257, 0);
    
        int max_len = 0;
        std::for_each(begin, end, [&](auto& str) {
            ++cnt[get(str)];
            max_len = std::max(max_len, static_cast<int>(str.length()));
        });
    
        if (max_len <= len) {
            return 0;
        }
    
        std::partial_sum(cnt.begin(), cnt.end(), pref_cnt.begin());
    
        std::for_each(std::make_reverse_iterator(end), std::make_reverse_iterator(begin), [&] (auto& str) {
            buffer[--pref_cnt[get(str)]] = std::move(str);
        });
    
        std::move(buffer.begin(), buffer.begin() + std::distance(begin, end), begin);
    
        size_t compCnt = 0;
        auto group_start = begin;
        for (int cnt_group : cnt) {
            if (cnt_group == 0) continue;
        
            if (cnt_group > 1) {
                compCnt += Sort<WithQuickSort>(group_start, group_start + cnt_group, len + 1);
            }
    
            group_start += cnt_group;
        }
        return compCnt;
    }

    s_iterator begin;
    s_iterator end;
    std::vector<std::string> buffer;
};

