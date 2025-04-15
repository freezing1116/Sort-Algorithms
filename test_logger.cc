#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
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

#include <functional>

struct Sorter {
    std::string name;
    std::function<void(std::vector<int>&)> sort_func;

    Sorter(std::string n, std::function<void(std::vector<int>&)> f)
        : name(std::move(n))
        , sort_func(std::move(f))
    {
    }
};

int main()
{
    std::vector<std::pair<std::string, std::function<void(std::vector<int>&)>>> algorithms = {
        { "Insertion", [](std::vector<int>& v) { insertion_sort(v); } },
        // { "Selection", [](std::vector<int>& v) { selection_sort(v); } },
        // { "Bubble", [](std::vector<int>& v) { bubble_sort(v); } },
        { "Heap", [](std::vector<int>& v) { heap_sort(v); } },
        // { "Merge", [](std::vector<int>& v) { merge_sort(v); } },
        { "Quick", [](std::vector<int>& v) { quick_sort(v); } },
        // { "Library", [](std::vector<int>& v) { library_sort(v); } },
        { "Tim", [](std::vector<int>& v) { tim_sort(v); } },
        { "Cocktail", [](std::vector<int>& v) { cocktail_sort(v); } },
        { "Comb", [](std::vector<int>& v) { comb_sort(v); } },
        { "Tournament", [](std::vector<int>& v) { tournament_sort(v); } },
        { "Intro", [](std::vector<int>& v) { intro_sort(v); } },
    };

    std::map<std::string, std::vector<std::pair<std::string, std::string>>> all_cases = {
        { "Ascending", { { "1K", "testcases_1K/test_asce_1K.txt" }, { "10K", "testcases_10K/test_asce_10K.txt" }, { "100K", "testcases_100K/test_asce_100K.txt" }, { "1M", "testcases_1M/test_asce_1M.txt" } } },
        // { "Descending", { { "1K", "testcases_1K/test_desc_1K.txt" }, { "10K", "testcases_10K/test_desc_10K.txt" }, { "100K", "testcases_100K/test_desc_100K.txt" }, { "1M", "testcases_1M/test_desc_1M.txt" } } },
        // { "Partially", { { "1K", "testcases_1K/test_part_1K.txt" }, { "10K", "testcases_10K/test_part_10K.txt" }, { "100K", "testcases_100K/test_part_100K.txt" }, { "1M", "testcases_1M/test_part_1M.txt" } } },
        // { "Random", { { "1K", "testcases_1K/test_rand_1K.txt" }, { "10K", "testcases_10K/test_rand_10K.txt" }, { "100K", "testcases_100K/test_rand_100K.txt" }, { "1M", "testcases_1M/test_rand_1M.txt" } } }
    };

    std::ofstream log("results_summary.txt");

    for (const auto& [case_name, size_vec] : all_cases) {
        log << "== " << case_name << " Data ==\n\n";

        log << std::setw(10) << "InputSize";
        for (const auto& algo : algorithms)
            log << std::setw(20) << algo.first;
        log << "\n";

        for (const auto& [size_label, file_path] : size_vec) {
            log << std::setw(10) << size_label;
            for (const auto& algo : algorithms) {
                std::ifstream infile(file_path);
                std::vector<int> data;
                int val;
                while (infile >> val)
                    data.push_back(val);
                std::vector<int> to_sort = data;

                auto start = std::chrono::high_resolution_clock::now();
                long mem_before = get_peak_memory_kb();
                algo.second(to_sort);
                long mem_after = get_peak_memory_kb();
                auto end = std::chrono::high_resolution_clock::now();

                double time_ms = std::chrono::duration<double, std::milli>(end - start).count();
                long mem_kb = mem_after - mem_before;

                log << std::setw(20)
                    << (std::to_string(time_ms).substr(0, 5) + "ms/" + std::to_string(mem_kb) + "KB");
            }

            log << "\n";
        }

        log << "\n";
    }

    log.close();
    std::cout << "📄 Results saved to results_summary.txt\n";
    return 0;
}
