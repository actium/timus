#include <iostream>

#include <cmath>

int main()
{
    constexpr double pi = 3.14159265359;

    unsigned n;
    std::cin >> n;

    if (n < 3) {
        std::cout << n << '\n';
    } else {
        std::cout << std::fixed << 1 + 1 / sin(pi / n) << '\n';
    }

    return 0;
}
