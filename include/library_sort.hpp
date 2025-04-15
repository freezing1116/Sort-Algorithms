#ifndef LNGD_LIBRARY_SORT_HPP
#define LNGD_LIBRARY_SORT_HPP

#include <algorithm>
#include <cmath>
#include <functional>
#include <numeric>
#include <type_traits>
#include <vector>

namespace LNGDSort {

template <typename T, typename Compare = std::less<T>>
class LNGDLibrarySorter {
private:
    std::vector<T> data;
    std::vector<T> buffer;
    Compare comp;
    int e = 1; // rebalancing factor

    bool is_equal(const T& a, const T& b) const
    {
        return !comp(a, b) && !comp(b, a);
    }

    int modifiedBinarySearch(const T& value)
    {
        int low = 0, high = static_cast<int>(data.size()) - 1;

        while (low <= high) {
            int mid = (low + high) / 2;
            int m1 = mid, m2 = mid;

            while (m1 >= low && is_equal(data[m1], T()))
                m1--;
            while (m2 <= high && is_equal(data[m2], T()))
                m2++;

            T left = (m1 >= low) ? data[m1] : value;
            T right = (m2 <= high) ? data[m2] : value;

            if (comp(value, left))
                high = m1 - 1;
            else if (comp(right, value))
                low = m2 + 1;
            else
                return m2;
        }

        return low;
    }

    // Helper to convert value to double if possible
    template <typename U = T>
    static auto to_double(const U& x) -> std::enable_if_t<std::is_arithmetic_v<U>, double>
    {
        return static_cast<double>(x);
    }

    template <typename U = T>
    static auto to_double(const U&) -> std::enable_if_t<!std::is_arithmetic_v<U>, double>
    {
        return 0.0; // fallback for non-numeric types
    }

    void reBalance()
    {
        int n = std::count_if(data.begin(), data.end(),
            [&](const T& x) { return !is_equal(x, T()); });
        if (n == 0)
            return;

        double mean = std::accumulate(data.begin(), data.end(), 0.0,
                          [&](double acc, const T& x) {
                              return !is_equal(x, T()) ? acc + to_double(x) : acc;
                          })
            / n;

        double stddev = 0.0;
        for (const auto& x : data) {
            if (!is_equal(x, T()))
                stddev += std::pow(to_double(x) - mean, 2);
        }
        stddev = std::sqrt(stddev / n);

        int ratio = static_cast<int>((n * mean / (stddev + 1e-9)) / 2);
        int ee = (2 * n) / std::max(1, ratio);
        int total_gaps = e + ee;

        buffer.clear();
        buffer.reserve(n + total_gaps);

        int j = 0;
        while (j < static_cast<int>(data.size())) {
            if (buffer.size() > 0 && buffer.size() % std::max(1, ratio) == 0 && total_gaps > 0) {
                total_gaps--;
                for (int g = 0; g < e + ee; ++g)
                    buffer.push_back(T()); // gap
            }
            if (!is_equal(data[j], T())) {
                buffer.push_back(data[j]);
            }
            j++;
        }

        data = buffer;
    }

public:
    LNGDLibrarySorter(int initial_size = 16, Compare c = Compare())
        : comp(c)
    {
        data.resize(initial_size, T()); // initialize with sentinel
    }

    void insert(const T& value)
    {
        int pos = modifiedBinarySearch(value);

        if (pos >= static_cast<int>(data.size())) {
            reBalance();
            insert(value);
            return;
        }

        if (is_equal(data[pos], T())) {
            data[pos] = value;
        } else {
            auto it = std::find_if(data.begin() + pos, data.end(), [&](const T& x) {
                return is_equal(x, T());
            });

            if (it == data.end()) {
                reBalance();
                insert(value);
                return;
            }

            for (auto rit = it; rit != data.begin() + pos; --rit) {
                if (rit == data.begin())
                    break;
                *rit = *(rit - 1);
            }
            data[pos] = value;
        }

        int gaps = std::count_if(data.begin(), data.end(), [&](const T& x) {
            return is_equal(x, T());
        });

        if (gaps < static_cast<int>(data.size() / 10)) {
            reBalance();
        }
    }
    std::vector<T> sorted() const
    {
        std::vector<T> result;
        for (const auto& val : data) {
            if (!is_equal(val, T()))
                result.push_back(val);
        }
        return result;
    }
};

} // namespace LNGDSort

// 외부 인터페이스 함수
template <typename T, typename Compare = std::less<T>>
void library_sort(std::vector<T>& arr, Compare comp = Compare())
{
    LNGDSort::LNGDLibrarySorter<T, Compare> sorter(16, comp);
    for (const auto& x : arr)
        sorter.insert(x);
    arr = sorter.sorted();
}

#endif // LNGD_LIBRARY_SORT_HPP
