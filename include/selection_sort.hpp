#ifndef SELECTION_SORT_HPP
#define SELECTION_SORT_HPP

#include <algorithm>
#include <functional> // for std::less
#include <vector>

template <typename T, typename Compare = std::less<T>>
void selection_sort(std::vector<T>& arr, Compare comp = Compare())
{
    int n = arr.size();

    for (int i = 0; i < n; ++i) {
        int min_index = i;

        // Find the minimum element in the unsorted part
        for (int j = i + 1; j < n; ++j) {
            if (comp(arr[j], arr[min_index])) {
                min_index = j;
            }
        }

        // Swap it with the first element in the unsorted part
        std::swap(arr[i], arr[min_index]);
    }
}

#endif // SELECTION_SORT_HPP
