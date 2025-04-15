#ifndef INSERTION_SORT_HPP
#define INSERTION_SORT_HPP

#include <functional> // for std::less
#include <vector>

template <typename T, typename Compare = std::less<T>>
void insertion_sort(std::vector<T>& arr, Compare comp = Compare())
{
    for (int i = 1; i < arr.size(); i++) {
        T key = arr[i];
        int j = i - 1;

        // arr[j] > key → comp(key, arr[j])
        while (j >= 0 && comp(key, arr[j])) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

#endif // INSERTION_SORT_HPP
