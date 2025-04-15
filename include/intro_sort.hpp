#ifndef INTRO_SORT_HPP
#define INTRO_SORT_HPP

#include <algorithm>
#include <cmath>
#include <functional>
#include <vector>

template <typename RandomIt, typename Compare>
RandomIt median_of_three(RandomIt a, RandomIt b, RandomIt c, Compare comp)
{
    if (comp(*a, *b)) {
        if (comp(*b, *c))
            return b;
        else if (comp(*a, *c))
            return c;
        else
            return a;
    } else {
        if (comp(*a, *c))
            return a;
        else if (comp(*b, *c))
            return c;
        else
            return b;
    }
}

template <typename RandomIt, typename Compare>
RandomIt introsort_partition(RandomIt low, RandomIt high, Compare comp)
{
    auto pivot = *high;
    RandomIt i = low - 1;
    for (RandomIt j = low; j < high; ++j) {
        if (!comp(pivot, *j)) { // *j <= pivot
            ++i;
            std::iter_swap(i, j);
        }
    }
    std::iter_swap(i + 1, high);
    return i + 1;
}

template <typename RandomIt, typename Compare>
void insertion_sort(RandomIt begin, RandomIt end, Compare comp)
{
    for (auto it = begin + 1; it <= end; ++it) {
        auto key = *it;
        auto j = it - 1;
        while (j >= begin && comp(key, *j)) {
            *(j + 1) = *j;
            --j;
        }
        *(j + 1) = key;
    }
}

template <typename RandomIt, typename Compare>
void introsort_util(RandomIt begin, RandomIt end, int depth_limit, Compare comp)
{
    int size = end - begin + 1;

    if (size < 16) {
        insertion_sort(begin, end, comp);
        return;
    }

    if (depth_limit == 0) {
        std::make_heap(begin, end + 1, comp);
        std::sort_heap(begin, end + 1, comp);
        return;
    }

    RandomIt pivot = median_of_three(begin, begin + size / 2, end, comp);
    std::iter_swap(pivot, end);
    RandomIt partition_point = introsort_partition(begin, end, comp);

    introsort_util(begin, partition_point - 1, depth_limit - 1, comp);
    introsort_util(partition_point + 1, end, depth_limit - 1, comp);
}

template <typename T, typename Compare = std::less<T>>
void intro_sort(std::vector<T>& arr, Compare comp = Compare())
{
    if (arr.empty())
        return;
    int depth_limit = 2 * std::log2(arr.size());
    introsort_util(arr.begin(), arr.end() - 1, depth_limit, comp);
}

#endif // INTRO_SORT_HPP
