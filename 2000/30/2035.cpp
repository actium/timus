#include <iostream>

int main()
{
    unsigned x, y, c;
    std::cin >> x >> y >> c;

    if (x + y < c) {
        std::cout << "Impossible" << '\n';
    } else {
        const unsigned a = std::min(x, c);
        std::cout << a << ' ' << c - a << '\n';
    }

    return 0;
}
