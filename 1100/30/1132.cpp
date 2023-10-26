#include <iostream>

unsigned raise(unsigned base, unsigned power, unsigned modulus)
{
    unsigned value = 1;
    while (power != 0) {
        if (power % 2 == 1)
            value = value * base % modulus;

        base = base * base % modulus;
        power /= 2;
    }
    return value;
}

int legendre_symbol(unsigned x, unsigned p)
{
    const unsigned ls = raise(x, (p - 1) / 2, p);
    return ls == p - 1 ? -1 : ls;
}

int solve(unsigned a, unsigned n)
{
    if (a != 1 && legendre_symbol(a, n) == -1)
        return -1;

    const unsigned e = __builtin_ctz(n - 1), s = (n - 1) / (1 << e);

    unsigned q = 2;
    while (legendre_symbol(q, n) != -1)
        ++q;

    unsigned x = raise(a, (s + 1) / 2, n);
    unsigned b = raise(a, s, n);
    unsigned g = raise(q, s, n);

    for (unsigned r = e, m; ; r = m) {
        m = 0;
        for (unsigned t = b; m < r && t != 1; ++m)
            t = raise(t, 2, n);

        if (m == 0)
            return x;

        const unsigned t = raise(g, 1 << r - m - 1, n);
        x = x * t % n;
        g = t * t % n;
        b = b * g % n;
   }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned k;
    std::cin >> k;

    while (k-- != 0) {
        unsigned a, n;
        std::cin >> a >> n;

        const int x = solve(a % n, n);
        if (x == -1) {
            std::cout << "No root" << '\n';
            continue;
        }

        if (x == n - x) {
            std::cout << x << '\n';
        } else {
            std::cout << std::min<unsigned>(x, n - x) << ' ' << std::max<unsigned>(x, n - x) << '\n';
        }
    }

    return 0;
}
