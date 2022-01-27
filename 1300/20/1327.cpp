#include <iostream>

int main()
{
    unsigned a, b;
    std::cin >> a >> b;

    std::cout << (b - a + b % 2 + a % 2) / 2 << '\n';

    return 0;
}
