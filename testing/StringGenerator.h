
#include <vector>
#include <string>
#include <random>
#include <ctime>

class StringGenerator {
public:
    StringGenerator();

    std::string generateRandomString(int length);

    std::vector<std::string> generateRandomStrings(int count, int minLength, int maxLength);

    std::vector<std::string> generateReverseSortedStrings(int count, int minLength, int maxLength);

    std::vector<std::string> almostSortedStrings(int count, int minLength, int maxLength, int cntSwaps = 10);

    std::vector<std::string> specialStringsArraysGenerator(int count, int minLength, int maxLength, int prefixSize);

    std::vector<std::string> getSubArray(const std::vector<std::string>& array, int subArraySize);

private:
    static const std::string symbols;
    std::mt19937 rng;
};
