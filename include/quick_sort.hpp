#ifndef QUICK_SORT_HPP
#define QUICK_SORT_HPP

#include <algorithm>
#include <functional>
#include <vector>

// ===== Helper Functions (템플릿화) =====

// Median-of-three pivot selection
template <typename T, typename Compare>
int median_of_three(std::vector<T>& arr, int low, int high, Compare comp)
{
    int mid = low + (high - low) / 2;

    if (comp(arr[mid], arr[low]))
        std::swap(arr[low], arr[mid]);
    if (comp(arr[high], arr[low]))
        std::swap(arr[low], arr[high]);
    if (comp(arr[high], arr[mid]))
        std::swap(arr[mid], arr[high]);

    std::swap(arr[mid], arr[high]); // median to end
    return high;
}

// Partition using Compare
template <typename T, typename Compare>
int partition(std::vector<T>& arr, int low, int high, Compare comp)
{
    T pivot = arr[high];
    int i = low;

    for (int j = low; j < high; ++j) {
        if (comp(arr[j], pivot)) {
            std::swap(arr[i], arr[j]);
            ++i;
        }
    }
    std::swap(arr[i], arr[high]);
    return i;
}

// Internal quick sort (tail-recursive)
template <typename T, typename Compare>
void quick_sort_impl(std::vector<T>& arr, int low, int high, Compare comp)
{
    while (low < high) {
        int pivot_index = median_of_three(arr, low, high, comp);
        int pi = partition(arr, low, high, comp);

        if (pi - low < high - pi) {
            quick_sort_impl(arr, low, pi - 1, comp);
            low = pi + 1;
        } else {
            quick_sort_impl(arr, pi + 1, high, comp);
            high = pi - 1;
        }
    }
}

// ===== External wrapper function =====
template <typename T, typename Compare = std::less<T>>
void quick_sort(std::vector<T>& arr, Compare comp = Compare())
{
    if (!arr.empty()) {
        quick_sort_impl(arr, 0, arr.size() - 1, comp);
    }
}

#endif // QUICK_SORT_HPP
