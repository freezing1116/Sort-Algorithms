#ifndef COCKTAIL_SORT_HPP
#define COCKTAIL_SORT_HPP

#include <algorithm>
#include <functional> // for std::less
#include <vector>

template <typename T, typename Compare = std::less<T>>
void cocktail_sort(std::vector<T>& a, Compare comp = Compare())
{
    int n = a.size();
    if (n <= 1)
        return;

    bool swapped = true;
    int start = 0;
    int end = n - 1;

    while (swapped) {
        swapped = false;

        // 왼쪽 -> 오른쪽
        for (int i = start; i < end; ++i) {
            if (comp(a[i + 1], a[i])) {
                std::swap(a[i], a[i + 1]);
                swapped = true;
            }
        }

        if (!swapped)
            break;

        swapped = false;
        --end;

        // 오른쪽 -> 왼쪽
        for (int i = end - 1; i >= start; --i) {
            if (comp(a[i + 1], a[i])) {
                std::swap(a[i], a[i + 1]);
                swapped = true;
            }
        }

        ++start;
    }
}

#endif // COCKTAIL_SORT_HPP
