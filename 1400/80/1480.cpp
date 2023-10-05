#include <iostream>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    std::cout << n * n + n / 2 + 1 << '\n';

    unsigned u = 1, v = n * n;
    for (unsigned i = 0; i < n; ++i) {
        for (unsigned j = 0; j < n; ++j) {
            if ((i + j) % 2 == 0)
                std::cout << v-- << ' ';
            else
                std::cout << u++ << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}
