#include "StringGenerator.h"

#include <algorithm>
#include <ctime>

StringGenerator::StringGenerator() {
    rng.seed(time(nullptr));
}

std::string StringGenerator::generateRandomString(int length) {
    std::uniform_int_distribution<size_t> dist(0, symbols.size() - 1);
    std::string result;
    result.reserve(length);
    for (int i = 0; i < length; ++i) {
        result += symbols[dist(rng)];
    }
    return result;
}

std::vector<std::string> StringGenerator::generateRandomStrings(int count, int minLength, int maxLength) {
    std::vector<std::string> result;
    result.reserve(count);
    std::uniform_int_distribution<int> lengthDist(minLength, maxLength);
    for (int i = 0; i < count; ++i) {
        result.push_back(generateRandomString(lengthDist(rng)));
    }
    return result;
}

std::vector<std::string> StringGenerator::generateReverseSortedStrings(int count, int minLength, int maxLength) {
    std::vector<std::string> result = generateRandomStrings(count, minLength, maxLength);
    std::sort(result.begin(), result.end(), std::greater<std::string>());
    return result;
}

std::vector<std::string> StringGenerator::almostSortedStrings(int count, int minLength, int maxLength, int cntSwaps) {
    std::vector<std::string> result = generateRandomStrings(count, minLength, maxLength);
    std::sort(result.begin(), result.end());
    if (count < 2) {
        return result;
    }
    cntSwaps = std::min(cntSwaps, count / 2);
    std::uniform_int_distribution<int> dist(0, count - 1);
    for (int i = 0; i < cntSwaps; ++i) {
        size_t position = dist(rng);
        std::swap(result[position], result[position + 1]);
    }
    return result;
}

std::vector<std::string> StringGenerator::specialStringsArraysGenerator(int count, int minLength, int maxLength, int prefixSize) {
    if (prefixSize == 0)
        return generateRandomStrings(count, minLength, maxLength);

    std::uniform_int_distribution<int> totalLenDist(minLength, maxLength);
    std::uniform_int_distribution<int> prefixLenDist(3, 8);

    std::vector<std::string> prefixes;
    prefixes.reserve(prefixSize);
    for (int i = 0; i < prefixSize; ++i) {
        int pLen = prefixLenDist(rng);
        prefixes.push_back(generateRandomString(pLen));
    }

    std::vector<std::string> result;
    result.reserve(count);
    std::uniform_int_distribution<int> prefixDist(0, prefixSize - 1);

    for (int i = 0; i < count; ++i) {
        int totalLen = totalLenDist(rng);
        const std::string &pref = prefixes[prefixDist(rng)];
        if ((int)pref.size() > totalLen) {
            result.push_back(pref.substr(0, totalLen));
        } else {
            int rest = totalLen - (int)pref.size();
            result.push_back(pref + generateRandomString(rest));
        }
    }

    return result;
}

std::vector<std::string> StringGenerator::getSubArray(const std::vector<std::string>& array, int subArraySize) {
    if (subArraySize >= array.size()) {
        return array;
    }
    return std::vector<std::string>(array.begin(), array.begin() + subArraySize);
}

const std::string StringGenerator::symbols = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#%:;^&*()-";

