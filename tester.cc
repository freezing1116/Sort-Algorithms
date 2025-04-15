#include <chrono>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <sys/resource.h>
#include <vector>

#include "include/all_sorts.hpp"

long get_peak_memory_kb()
{
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss;
}

struct Sorter {
    std::string name;
    std::function<void(std::vector<int>&)> sort_func;
};

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: ./tester <input_file>\n";
        return 1;
    }

    std::ifstream infile(argv[1]);
    if (!infile.is_open()) {
        std::cerr << "Cannot open file: " << argv[1] << '\n';
        return 1;
    }
    long before_vec = get_peak_memory_kb();
    std::vector<int> data;
    int val;
    while (infile >> val)
        data.push_back(val);

    std::vector<Sorter> algorithms = {
        // { "Insertion", [](std::vector<int>& v) { insertion_sort(v); } },
        // { "Selection", [](std::vector<int>& v) { selection_sort(v); } },
        // { "Bubble", [](std::vector<int>& v) { bubble_sort(v); } },
        { "Heap", [](std::vector<int>& v) { heap_sort(v); } },
        { "Merge", [](std::vector<int>& v) { merge_sort(v); } },
        { "Quick", [](std::vector<int>& v) { quick_sort(v); } },
        // { "Library", [](std::vector<int>& v) { library_sort(v); } },
        { "Tim", [](std::vector<int>& v) { tim_sort(v); } },
        { "Cocktail", [](std::vector<int>& v) { cocktail_sort(v); } },
        { "Comb", [](std::vector<int>& v) { comb_sort(v); } },
        { "Tournament", [](std::vector<int>& v) { tournament_sort(v); } },
        { "Intro", [](std::vector<int>& v) { intro_sort(v); } },
    };

    for (const auto& algo : algorithms) {
        std::vector<int> to_sort = data;

        auto start = std::chrono::high_resolution_clock::now();
        long mem_before_kb = get_peak_memory_kb();
        algo.sort_func(to_sort);
        long mem_after_kb = get_peak_memory_kb();
        auto end = std::chrono::high_resolution_clock::now();

        std::cout << "== " << algo.name << " ==\n";
        std::cout << "Sorted? " << (std::is_sorted(to_sort.begin(), to_sort.end()) ? "✅ Yes" : "❌ No") << '\n';
        std::cout << "Time: " << std::chrono::duration<double, std::milli>(end - start).count() << " ms\n";
        std::cout << "Memory: " << mem_after_kb - mem_before_kb << " KB\n\n";
    }

    return 0;
}
