#ifndef TIM_SORT_HPP
#define TIM_SORT_HPP

#include <algorithm>
#include <functional>
#include <vector>

const int RUN = 32;

// insertion sort with Compare
template <typename T, typename Compare>
void insertion_sort(std::vector<T>& arr, int left, int right, Compare comp)
{
    for (int i = left + 1; i <= right; i++) {
        T temp = arr[i];
        int j = i - 1;
        while (j >= left && comp(temp, arr[j])) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

// merge function with Compare
template <typename T, typename Compare>
void tim_merge(std::vector<T>& arr, int left, int mid, int right, Compare comp)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<T> L(n1), R(n2);
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (!comp(R[j], L[i])) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
}

// full tim_sort
template <typename T, typename Compare = std::less<T>>
void tim_sort(std::vector<T>& arr, Compare comp = Compare())
{
    int n = arr.size();

    // sort individual runs
    for (int i = 0; i < n; i += RUN)
        insertion_sort(arr, i, std::min(i + RUN - 1, n - 1), comp);

    // merge runs of increasing size
    for (int size = RUN; size < n; size *= 2) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = std::min(left + 2 * size - 1, n - 1);
            if (mid < right)
                tim_merge(arr, left, mid, right, comp);
        }
    }
}

#endif // TIM_SORT_HPP
