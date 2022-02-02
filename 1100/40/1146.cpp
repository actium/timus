#include <iostream>
#include <vector>

constexpr int oo = 1270000;

int main()
{
    size_t n;
    std::cin >> n;

    std::vector<std::vector<int>> a(1+n, std::vector<int>(n));
    for (size_t i = 1; i <= n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            std::cin >> a[i][j];

            a[i][j] += a[i-1][j];
        }
    }

    int k = -oo;
    for (size_t i1 = 1; i1 <= n; ++i1) {
        for (size_t i2 = 0; i2 < i1; ++i2) {
            int x = 0, y = -oo;
            for (size_t j = 0; j < n; ++j) {
                const int q = a[i1][j] - a[i2][j];
                x = std::max(q, x + q);
                y = std::max(y, x);
            }

            k = std::max(k, y);
        }
    }

    std::cout << k << '\n';

    return 0;
}
