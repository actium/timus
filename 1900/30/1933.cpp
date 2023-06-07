#include <iostream>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    const unsigned k = 2 * n + 1;

    for (unsigned i = 0; i < k; ++i) {
        for (unsigned j = 0; j < i; ++j)
            std::cout << (k - 2 * (i + j + 1) % k) % k + 1 << ' ';

        std::cout << '0';

        for (unsigned j = i + 1; j < k; ++j)
            std::cout << ' ' << (k - 2 * (i + j + 1) % k) % k + 1;

        std::cout << '\n';
    }

    return 0;
}
