#include <iostream>
#include "processing/processing.hpp"

int main() {
    std::string inputFile;
    std::cin >> inputFile;
    std::ifstream input(inputFile);
    Virtual myCpu(&input);
    myCpu.read();
    myCpu.execute();
    return 0;
}