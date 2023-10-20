#include <iostream>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    for (unsigned i = 0; i < n; ++i) {
        if (n % 2 == 1 || i < n / 2)
            std::cout << (i % 2 == 0 ? 1 + i : n - i) << ' ';
        else
            std::cout << (i % 2 == 0 ? n - i : 1 + i) << ' ';
    }
    std::cout << '\n';

    for (unsigned i = 0; i < n; ++i) {
        std::cout << (i < (n + 1) / 2 ? 1 + 2 * i : 2 * (n - i)) << ' ';
    }
    std::cout << '\n';

    return 0;
}
