#include <iostream>

int& bru()
{
    int x = 1;
    return x;
}

int main() {
    std::cout << &bru();
    return 0;
}