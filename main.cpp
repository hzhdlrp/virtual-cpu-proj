#include <iostream>
#include "processing/processing.hpp"

int main() {
    std::string inputFile("/Users/vadimleonov/CLionProjects/virtual_cpu_project/test-programs/factorial");
//    std::cin >> inputFile;
//    /Users/vadimleonov/Desktop/алгосы/virtual-cpu-tests/fibo
    std::ifstream input(inputFile);
    Virtual myCpu(&input);
    myCpu.read();
    myCpu.execute();
    return 0;
}