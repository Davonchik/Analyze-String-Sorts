#include <iostream>
#include <fstream>

#include "testing/StringSortTester.h"

#include "sort/classic/sort.h"
#include "sort/special/sort.h"

void ToFile(const std::string& path, const std::vector<SortingTestResult>& data) {
    std::ofstream out(path);
    for (const auto& record : data) {
        out << record.size << " " << record.comparsionsCnt << " " << record.timeMs << "\n";
    }
}


int main() {
    using str_vec = std::vector<std::string>;

    auto testAll = [](StringSortTester::Type type, std::string pathBase) {
        StringSortTester tester;

        tester.InitTestingData(type);
       
        // Random
        std::cout << "Processing: " << pathBase + "/ClassicMergeSort.txt" << std::endl;
        ToFile(pathBase + "/ClassicMergeSort.txt", tester.testSorting([](str_vec& data) {
            return mergeSort(data);
        }));
        std::cout << "Processing: " << pathBase + "/ClassicQuickSort.txt" << std::endl;
        ToFile(pathBase + "/ClassicQuickSort.txt", tester.testSorting([](str_vec& data) {
            return quickSort(data.begin(), data.end());
        }));
        std::cout << "Processing: " << pathBase + "/StringMergeSort.txt" << std::endl;
        ToFile(pathBase + "/StringMergeSort.txt", tester.testSorting([](str_vec& data) {
            return StringMergeSort(data.begin(), data.end());
        }));
        std::cout << "Processing: " << pathBase + "/StringTernaryQuickSort.txt" << std::endl;
        ToFile(pathBase + "/StringTernaryQuickSort.txt", tester.testSorting([](str_vec& data) {
            return StringTernaryQuickSort(data.begin(), data.end());
        }));
        std::cout << "Processing: " << pathBase + "/StringTernaryQuickSortPrinceton.txt" << std::endl;
        ToFile(pathBase + "/StringTernaryQuickSortPrinceton.txt", tester.testSorting([](str_vec& data) {
            return StringTernaryQuickSortPrinceton(data.begin(), 0, data.size() - 1, 0);
        }));
        std::cout << "Processing: " << pathBase + "/MsdStringSort.txt" << std::endl;
        ToFile(pathBase + "/MsdStringSort.txt", tester.testSorting([](str_vec& data) {
            return MsdStringSort(data.begin(), data.end());
        }));
        std::cout << "Processing: " << pathBase + "/MsdQuickStringSort.txt" << std::endl;
        ToFile(pathBase + "/MsdQuickStringSort.txt", tester.testSorting([](str_vec& data) {
            return MsdQuickStringSort(data.begin(), data.end());
        }));

    };

    { // test 1
        testAll(StringSortTester::Type::random, "../results/random");
    }

    { // test 2
        testAll(StringSortTester::Type::nearSorted, "../results/near_sorted");
    }

    { // test 3
        testAll(StringSortTester::Type::reversed, "../results/reversed");
    }

    { // test 4
        testAll(StringSortTester::Type::specialBigLcpStrings, "../results/special");
    }

    return 0;
}