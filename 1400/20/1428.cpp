#include <iostream>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned a, b, c;
    std::cin >> a >> b >> c;

    const unsigned x = 1u << (c - 1) / a;
    const unsigned y = 1u << (c - 1) / b;

    std::cout << x << '\n';
    std::cout << y << '\n';
    std::cout << 2 << '\n';

    return 0;
}
