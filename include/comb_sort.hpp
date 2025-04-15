#ifndef COMB_SORT_HPP
#define COMB_SORT_HPP

#include <algorithm>
#include <functional> // for std::less
#include <vector>

// 갭 계산 함수
static int getNextGap(int gap)
{
    gap = (gap * 10) / 13;
    return (gap < 1) ? 1 : gap;
}

// 템플릿 comb sort
template <typename T, typename Compare = std::less<T>>
void comb_sort(std::vector<T>& a, Compare comp = Compare())
{
    int n = a.size();
    int gap = n;
    bool swapped = true;

    while (gap != 1 || swapped) {
        gap = getNextGap(gap);
        swapped = false;

        for (int i = 0; i < n - gap; ++i) {
            if (comp(a[i + gap], a[i])) {
                std::swap(a[i], a[i + gap]);
                swapped = true;
            }
        }
    }
}

#endif // COMB_SORT_HPP
