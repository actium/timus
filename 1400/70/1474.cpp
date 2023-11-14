#include <iostream>
#include <vector>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    std::vector<unsigned> w(n), b(n);
    for (unsigned i = 0; i < n; ++i) {
        w[i] = i;
        b[i] = n + i + 1;
    }

    std::cout << (n + 1) * (n + 1) - 1 << '\n';
    for (unsigned i = 0, k = 1, x = n; i <= 2 * n; k -= (i > n), ++i, k += (i < n)) {
        if (i % 2 == 0) {
            int p = n - 1;
            while (p >= 0 && w[p] > x)
                --p;

            for (unsigned j = 0; j < k && p >= 0; ++j, --p) {
                std::cout << w[p] << ' ';
                std::swap(w[p], x);
            }
        } else {
            int p = 0;
            while (p < n && b[p] < x)
                ++p;

            for (unsigned j = 0; j < k && p < n; ++j, ++p) {
                std::cout << b[p] << ' ';
                std::swap(b[p], x);
            }
        }
    }

    return 0;
}
