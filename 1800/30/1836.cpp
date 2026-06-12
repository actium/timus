#include <iostream>

void error()
{
    std::cout << "error" << '\n';
}

void ambiguous()
{
    std::cout << "ambiguous" << '\n';
}

void answer(double v)
{
    std::cout << std::fixed << v << '\n';
}

void solve(unsigned a, unsigned h[4])
{
    unsigned z = 0;
    for (size_t i = 0; i < 4; ++i) {
        if (h[i] == 0)
            z |= 1 << i;
    }

    const auto handle_single_zero = [&](size_t x) {
        const auto p = h[(x+3)%4], q = h[(x+2)%4], r = h[(x+1)%4];
        if (p + r > q)
            return error();

        const double m = q - (p + r), d = 6.0 * (p + m) * (r + m), s = 0.5 * (p + r);
        return answer(1.0 * a * a * (s + m * m * m / d));
    };

    switch (__builtin_popcount(z)) {
        case 4:
            return answer(0);

        case 3:
            return ambiguous();

        case 2:
            return z == 5 || z == 10 ? error() : ambiguous();

        case 1:
            return handle_single_zero(__builtin_ctz(z));

        case 0:
            return h[0] + h[2] != h[1] + h[3] ? error() : answer(0.25 * a * a * (h[0] + h[1] + h[2] + h[3]));
    }
}

void test_case()
{
    unsigned a;
    std::cin >> a;

    unsigned h[4];
    for (size_t i = 0; i < 4; ++i)
        std::cin >> h[i];

    solve(a, h);
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t t;
    std::cin >> t;

    while (t-- > 0)
        test_case();

    return 0;
}
