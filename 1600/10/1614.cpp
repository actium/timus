#include <iostream>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    const size_t m = 2 * n;

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0, k = i; j < m; k += ++j)
            std::cout << 1 + k % m << ' ';

        std::cout << '\n';
    }

    return 0;
}
