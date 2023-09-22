#include <iostream>

unsigned C(unsigned n, unsigned k)
{
    unsigned v = n;

    for (unsigned i = n - k + 1; i < n; ++i)
        v *= i;

    for (unsigned i = 2; i <= k; ++i)
        v /= i;

    return v;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m;
    std::cin >> n >> m;

    bool h = false;
    for (size_t i = 0; i < m; ++i) {
        unsigned x;
        std::cin >> x;

        if (x == 1)
            h = true;
    }

    unsigned k = 0;

    if (m >= n / 3 && h)
        k += C(n - m, 2);

    if (m >= n / 3 && !h)
        k += m * (n - m - 1);

    if (m > n / 3 && h)
        k += (m - 1) * (n - m);

    if (m > n / 3 && !h)
        k += C(m, 2);

    if (m > n / 3 + 1 && h)
        k += C(m - 1, 2);

    std::cout << k << '\n';

    return 0;
}
