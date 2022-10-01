#include <iostream>

int main()
{
    unsigned n;
    std::cin >> n;

    std::cout << 2 * n << '\n';
    for (unsigned i = 1; i <= n; ++i)
        std::cout << i << ' ';
    for (unsigned i = n; i >= 1; --i)
        std::cout << i << ' ';

    return 0;
}
