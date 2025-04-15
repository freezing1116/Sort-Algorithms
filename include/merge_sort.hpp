#ifndef MERGE_SORT_HPP
#define MERGE_SORT_HPP

#include <functional> // for std::less
#include <vector>

// 병합 함수 (generic)
template <typename T, typename Compare = std::less<T>>
static void merge(std::vector<T>& arr, int left, int mid, int right, Compare comp = Compare())
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<T> L(n1), R(n2);
    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (!comp(R[j], L[i])) { // equivalent to: L[i] <= R[j]
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

// 내부 재귀 함수 (generic)
template <typename T, typename Compare = std::less<T>>
static void merge_sort_impl(std::vector<T>& arr, int left, int right, Compare comp = Compare())
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    merge_sort_impl(arr, left, mid, comp);
    merge_sort_impl(arr, mid + 1, right, comp);
    merge(arr, left, mid, right, comp);
}

// 외부 호출 함수
template <typename T, typename Compare = std::less<T>>
void merge_sort(std::vector<T>& arr, Compare comp = Compare())
{
    if (!arr.empty()) {
        merge_sort_impl(arr, 0, arr.size() - 1, comp);
    }
}

#endif // MERGE_SORT_HPP
