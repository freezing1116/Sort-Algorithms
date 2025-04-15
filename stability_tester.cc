#include "include/all_sorts.hpp"
#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

struct Item {
    int key;
    std::string label;

    bool operator<(const Item& other) const
    {
        return key < other.key;
    }
};

// 안정성 검사
bool is_stable(const std::vector<Item>& original, const std::vector<Item>& sorted)
{
    std::multimap<int, std::string> expected;
    for (const auto& item : original) {
        expected.emplace(item.key, item.label);
    }

    for (const auto& item : sorted) {
        auto range = expected.equal_range(item.key);
        if (range.first == range.second || range.first->second != item.label) {
            return false;
        }
        expected.erase(range.first);
    }
    return true;
}

// 단일 알고리즘 안정성 검사
void test_sort_stability(const std::string& algo_name,
    const std::function<void(std::vector<Item>&)>& sort_func,
    std::ostream& os = std::cout)
{
    std::vector<std::vector<Item>> test_cases = {
        { { 3, "A" }, { 1, "B" }, { 2, "C" }, { 3, "D" }, { 2, "E" }, { 1, "F" } },
        { { 5, "X" }, { 5, "Y" }, { 4, "Z" }, { 5, "W" }, { 4, "Q" }, { 4, "R" } },
        { { 10, "a" }, { 10, "b" }, { 10, "c" }, { 9, "d" }, { 9, "e" }, { 8, "f" } },
        { { 3, "A" }, { 1, "B" }, { 2, "C" }, { 3, "D" }, { 2, "E" }, { 1, "F" }, { 5, "X" }, { 5, "Y" }, { 4, "Z" }, { 5, "W" }, { 4, "Q" }, { 4, "R" } }
    };

    bool overall_stable = true;
    for (const auto& data : test_cases) {
        std::vector<Item> original = data;
        std::vector<Item> sorted = data;
        sort_func(sorted);

        if (!is_stable(original, sorted)) {
            overall_stable = false;
            break;
        }
    }

    os << "== " << algo_name << " ==\n";
    os << (overall_stable ? "✅ Stable\n" : "❌ Not stable\n");
}

// 여러 알고리즘 자동 테스트
void test_multiple_algorithms_stability(
    const std::vector<std::pair<std::string, std::function<void(std::vector<Item>&)>>>& algorithms,
    std::ostream& os = std::cout)
{
    for (const auto& [name, func] : algorithms) {
        test_sort_stability(name, func, os);
    }
}

int main()
{
    std::vector<std::pair<std::string, std::function<void(std::vector<Item>&)>>> algorithms = {
        { "Insertion", [](std::vector<Item>& v) { insertion_sort(v); } },
        { "Selection", [](std::vector<Item>& v) { selection_sort(v); } },
        { "Bubble", [](std::vector<Item>& v) { bubble_sort(v); } },
        { "Heap", [](std::vector<Item>& v) { heap_sort(v); } },
        { "Merge", [](std::vector<Item>& v) { merge_sort(v); } },
        { "Quick", [](std::vector<Item>& v) { quick_sort(v); } },
        // { "Library", [](std::vector<Item>& v) { library_sort(v); } },
        { "Tim", [](std::vector<Item>& v) { tim_sort(v); } },
        { "Cocktail", [](std::vector<Item>& v) { cocktail_sort(v); } },
        { "Comb", [](std::vector<Item>& v) { comb_sort(v); } },
        { "Tournament", [](std::vector<Item>& v) { tournament_sort(v); } },
        { "Intro", [](std::vector<Item>& v) { intro_sort(v); } },
    };

    // 결과 파일에 저장
    std::ofstream log("stability_results.txt");
    test_multiple_algorithms_stability(algorithms, log);
    log.close();

    // 콘솔 출력
    test_multiple_algorithms_stability(algorithms);

    return 0;
}
