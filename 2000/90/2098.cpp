#include <iostream>

int main()
{
    unsigned b;
    std::cin >> b;

    unsigned c, d;
    std::cin >> c >> d;

    unsigned k, p;
    std::cin >> k >> p;

    double x = b, y = 0;
    for (unsigned i = 1; i <= k; ++i) {
        x += c + i * d;
        y += (c + i * d) * (100 + p);
    }
    y /= 100.0;

    if (x < y) {
        std::cout << "Cash" << '\n';
        std::cout << std::fixed << y - x << '\n';
    } else {
        std::cout << "Insurance" << '\n';
        std::cout << std::fixed << x - y << '\n';
    }

    return 0;
}
