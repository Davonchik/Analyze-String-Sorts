#include <vector>
#include <string>
#include <chrono>
#include <cassert>
#include <functional>
#include <iostream>

#include "StringGenerator.h"

struct SortingTestResult {
    int size;
    double timeMs;
    double comparsionsCnt;
};

class StringSortTester {
public:
    enum class Type {
        random,
        reversed,
        nearSorted,
        specialBigLcpStrings
    };

    StringSortTester();

    void InitTestingData(Type type);

    std::vector<SortingTestResult> testSorting(std::function<size_t(std::vector<std::string>&)> sort) {
        assert(testingDataInitilized);

        std::vector<SortingTestResult> results;
        results.reserve(arrays.size());
        for (int i = 0; i < arrays.size(); i += 5) {
            SortingTestResult result;
            result.comparsionsCnt = 0;
            result.timeMs = 0;
            for (int j = 0; j < 5; ++j) {
                auto copy = arrays[i + j];
                
                result.size = copy.size();

                const auto start = std::chrono::high_resolution_clock::now();

                result.comparsionsCnt += sort(copy);

                const auto end = std::chrono::high_resolution_clock::now();

                const std::chrono::duration<double> diff = end - start;
                result.timeMs += std::chrono::duration_cast<std::chrono::microseconds>(diff).count();

                if (!isSorted(copy)) {
                    std::cout << "INCORRECT RESULT" << std::endl;
                }
            }
            result.comparsionsCnt /= 5.;
            result.timeMs /= 5.;
            results.push_back(result);
        }
        return results;
    }
private:
    StringGenerator gen;

    bool testingDataInitilized;

    std::vector<std::vector<std::string>> arrays;

    bool isSorted(const std::vector<std::string>& array);
    
};
