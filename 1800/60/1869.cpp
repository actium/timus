#include <iostream>
#include <vector>

int main()
{
    size_t n;
    std::cin >> n;

    std::vector<std::vector<unsigned>> a(n, std::vector<unsigned>(n));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j)
            std::cin >> a[i][j];
    }

    unsigned q = 0;
    for (unsigned t = 0; t < 2; ++t) {
        unsigned k = 0;
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < i; ++j)
                k -= a[j][i];

            for (size_t j = i; j < n; ++j)
                k += a[i][j];

            q = std::max(q, k);
        }

        for (size_t i = 0; i < n; ++i) {
            for (size_t j = i; j < n; ++j)
                a[i][j] = a[j][i];
        }
    }

    std::cout << (q + 35) / 36 << '\n';

    return 0;
}
