#include <iostream>

#include <cmath>

int main()
{
    unsigned n;
    std::cin >> n;

    std::cout << -int((n & ~1) * log(0.5) / log(10)) << '\n';

    return 0;
}
