#ifndef HEAP_SORT_HPP
#define HEAP_SORT_HPP

#include <algorithm>
#include <functional> // for std::less
#include <vector>

template <typename T, typename Compare = std::less<T>>
static void heapify(std::vector<T>& arr, int n, int i, Compare comp = Compare())
{
    int largest = i; // root
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    // NOTE: comp(a, b) == true  ⇔  a < b
    if (l < n && comp(arr[largest], arr[l])) {
        largest = l;
    }
    if (r < n && comp(arr[largest], arr[r])) {
        largest = r;
    }

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest, comp);
    }
}

template <typename T, typename Compare = std::less<T>>
void heap_sort(std::vector<T>& arr, Compare comp = Compare())
{
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, comp);
    }

    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0, comp);
    }
}

#endif // HEAP_SORT_HPP
