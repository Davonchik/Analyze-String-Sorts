
#include "StringSortTester.h"

StringSortTester::StringSortTester() : testingDataInitilized (false) {
}

void StringSortTester::InitTestingData(Type type) {
    assert(!testingDataInitilized);
    for (size_t i = 100; i <= 3000; i += 100) {
        for (int j = 0; j < 5; ++j) {
            switch (type) {
            case Type::random:
                arrays.push_back(gen.generateRandomStrings(i, 10, 200));
                break;
            case Type::reversed:
                arrays.push_back(gen.generateReverseSortedStrings(i, 10, 200));
                break;
            case Type::nearSorted:
                arrays.push_back(gen.almostSortedStrings(i, 10, 200));
                break;
            case Type::specialBigLcpStrings:
                arrays.push_back(gen.specialStringsArraysGenerator(i, 10, 200, 7));
                break;
            default:
                break;
            } 
        }
    }
    testingDataInitilized = true;
}

bool StringSortTester::isSorted(const std::vector<std::string>& array) {
    return std::is_sorted(array.begin(), array.end());
}
