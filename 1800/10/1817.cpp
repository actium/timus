#include <iostream>

double p[1 << 20] = { 1 };

unsigned next(unsigned x)
{
    const unsigned a = (x | (x - 1)) + 1;
    const unsigned b = (a & -a) / (x & -x);
    const unsigned c = a | ((b >> 1) - 1);
    return c;
}

double solve(unsigned n, unsigned k)
{
    if (k == 0) {
        for (unsigned i = 0; i < n; ++i)
            p[1 << i] = 1.0 / n;

        return 0;
    }

    double v = 0;

    const unsigned b = (1 << k) - 1, mask = (1 << n) - 1;
    for (unsigned i = b; i >= b; i = next(i) & mask) {
        if (p[i] == 0)
            continue;

        const auto dt = p[i] / n;
        for (unsigned j = 0; j < n; ++j) {
            unsigned c = j;
            while ((i & 1 << c % n) != 0)
                ++c;

            v += dt * (c - j);
            p[i | 1 << c % n] += dt;
        }
    }

    return v;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    for (unsigned k = 0; k < n; ++k)
        std::cout << std::fixed << solve(n, k) << '\n';

    return 0;
}
