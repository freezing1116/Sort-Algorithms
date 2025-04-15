#ifndef TOURNAMENT_SORT_HPP
#define TOURNAMENT_SORT_HPP

#include <functional>
#include <limits>
#include <vector>

template <typename T, typename Compare = std::less<T>>
class TournamentSorter {
private:
    std::vector<T> values; // 실제 정렬할 값 복사본
    std::vector<int> tree; // 토너먼트 트리: 인덱스 저장
    Compare comp;
    int n;

    // 두 인덱스 중 더 작은 값의 인덱스를 반환
    int winner(int i, int j)
    {
        if (i >= n)
            i -= n;
        if (j >= n)
            j -= n;
        return comp(values[i], values[j]) ? i : j;
    }

    void build_tree()
    {
        for (int i = 0; i < n; ++i)
            tree[n + i] = i; // leaf node: index

        for (int i = n - 1; i > 0; --i)
            tree[i] = winner(tree[2 * i], tree[2 * i + 1]);
    }

    void replace_winner(int index)
    {
        int pos = n + index;
        tree[pos] = -1; // 삭제된 상태로 표시

        while (pos > 1) {
            int sibling = (pos % 2 == 0) ? pos + 1 : pos - 1;
            int parent = pos / 2;

            if (tree[sibling] == -1)
                tree[parent] = tree[pos];
            else if (tree[pos] == -1)
                tree[parent] = tree[sibling];
            else
                tree[parent] = winner(tree[pos], tree[sibling]);

            pos = parent;
        }
    }

public:
    TournamentSorter(const std::vector<T>& input, Compare cmp = Compare())
        : values(input)
        , comp(cmp)
        , n(input.size())
    {
        tree.resize(2 * n, -1);
    }

    std::vector<T> sort()
    {
        std::vector<T> result;
        result.reserve(n);
        build_tree();

        for (int i = 0; i < n; ++i) {
            int winner_idx = tree[1];
            result.push_back(values[winner_idx]);

            // 사실상 삭제: 현재 우승자를 최대값으로 덮어쓰기
            values[winner_idx] = T(); // 무의미한 값으로 덮음 (safe, 내부에서만 사용)
            replace_winner(winner_idx);
        }

        return result;
    }
};

// 외부 인터페이스
template <typename T, typename Compare = std::less<T>>
void tournament_sort(std::vector<T>& arr, Compare comp = Compare())
{
    TournamentSorter<T, Compare> sorter(arr, comp);
    arr = sorter.sort();
}

#endif // TOURNAMENT_SORT_HPP
