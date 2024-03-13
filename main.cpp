#include <iostream>
#include "my-stack/Stack.hpp"


int main() {
    Stack<int> a;
    a.push(6);
    a.push(7);
    std::cout << a.top();

    return 0;
}