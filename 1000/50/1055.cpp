#include <iostream>
#include <vector>

std::vector<unsigned> primes(unsigned ub)
{
    std::vector<unsigned> p;

    unsigned x = 3;
    if (x <= ub)
        p.push_back(2);

    bool c[1+50000] = {};
    for (unsigned i = 9; i < ub; i += 4 * ++x, ++x) {
        if (c[x])
            continue;

        p.push_back(x);

        for (unsigned j = i; j < ub; j += 2 * x)
            c[j] = true;
    }
    while (x < ub) {
        if (!c[x])
            p.push_back(x);

        x += 2;
    }

    return p;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, m;
    std::cin >> n >> m;

    const std::vector<unsigned> p = primes(n + 1);

    std::vector<unsigned> h(p.size());

    const auto f = [&](unsigned n, int d) {
        for (size_t i = 0; i < p.size(); ++i) {
            for (unsigned q = p[i]; q <= n; q *= p[i])
                h[i] += n / q * d;
        }
    };

    f(n, +1);
    f(m, -1);
    f(n - m, -1);

    unsigned k = 0;
    for (const unsigned q : h)
        k += (q > 0);

    std::cout << k << '\n';

    return 0;
}
