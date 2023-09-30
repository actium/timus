#include <iostream>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, k, m;
    std::cin >> n >> k >> m;

    std::cout << "YES" << '\n';
    for (size_t i = 0; i < k; ++i) {
        size_t q;
        std::cin >> q;

        unsigned s = 0;
        for (size_t j = 0; j < q; ++j) {
            unsigned x;
            std::cin >> x;

            s += x;
        }

        std::cout << 1 + s % m << '\n';
    }

    return 0;
}
