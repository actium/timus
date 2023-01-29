#include <iostream>
#include <vector>

constexpr unsigned oo = ~0u;

uint8_t f[1 + 10000000];

unsigned solve(const std::vector<unsigned>& a)
{
    uint8_t k = 0;
    for (unsigned x : a) {
        for (unsigned d = 2; d * d <= x; ++d) {
            if (x % d != 0)
                continue;

            k = std::max(k, ++f[d]);
            if (k == 3)
                return oo;

            while (x % d == 0)
                x /= d;
        }
        if (x != 1) {
            k = std::max(k, ++f[x]);
            if (k == 3)
                return oo;
        }
    }
    return k;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<unsigned> a(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> a[i];

    const unsigned k = solve(a);
    if (k == oo) {
        std::cout << "infinity" << '\n';
    } else {
        std::cout << k << '\n';
    }

    return 0;
}
