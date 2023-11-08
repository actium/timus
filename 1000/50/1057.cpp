#include <iostream>
#include <vector>

unsigned solve(unsigned x, unsigned y, unsigned k, unsigned b)
{
    std::vector<unsigned> a;
    for (unsigned long long v = 1; v < y; v *= b)
        a.push_back(v);

    const auto first = [](unsigned c) {
        return (1 << c) - 1;
    };

    const auto next = [](unsigned v) {
        const unsigned a = (v | (v - 1)) + 1;
        const unsigned b = 1 << __builtin_ctz(a) - __builtin_ctz(v) - 1;
        return a | (b - 1);
    };

    const auto sum = [&](unsigned mask) {
        unsigned v = 0;
        while (mask != 0) {
            v += a[__builtin_ctz(mask)];
            mask -= mask & -mask;
        }
        return v;
    };

    const unsigned mask = first(a.size());

    unsigned q = 0;
    for (unsigned o = first(k), i = o; i >= o; i = next(i) & mask) {
        const unsigned v = (b == 2 ? i : sum(i));
        q += (v >= x && v <= y);
    }
    return q;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned x, y;
    std::cin >> x >> y;

    unsigned k, b;
    std::cin >> k >> b;

    std::cout << solve(x, y, k, b) << '\n';

    return 0;
}
