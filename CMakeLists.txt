cmake_minimum_required(VERSION 3.17)

project(StringSortings)

set(CMAKE_CXX_STANDARD 20)

set(sources 
    testing/StringGenerator.cpp 
    testing/StringSortTester.cpp
    
    sort/classic/MergeSort.cpp 
    sort/classic/QuickSort.cpp 

    sort/special/StringMergeSort.cpp
    sort/special/StringTernaryQuickSort.cpp
    sort/special/MsdStringSort.cpp
    sort/special/MsdQuickStringSort.cpp
)

# add_compile_options(-fsanitize=address)
# add_link_options(-fsanitize=address)

add_executable(SortTester main.cpp ${sources})
target_include_directories(SortTester PUBLIC sort sort/classic sort/special testing)
