#ifndef BUBBLE_SORT_HPP
#define BUBBLE_SORT_HPP

#include <algorithm>
#include <functional> // for std::less
#include <vector>

template <typename T, typename Compare = std::less<T>>
void bubble_sort(std::vector<T>& arr, Compare comp = Compare())
{
    int n = arr.size();
    for (int i = 0; i <= n - 2; ++i) {
        for (int j = 0; j <= n - 2; ++j) {
            if (comp(arr[j + 1], arr[j])) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

#endif // BUBBLE_SORT_HPP
