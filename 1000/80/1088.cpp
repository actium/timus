#include <iostream>

int main()
{
    unsigned d, e, f, dp, ep, h;
    std::cin >> d >> e >> f >> dp >> ep >> h;

    unsigned k = 0;
    {
        unsigned u = ((1 << f) + dp - 1) >> d, v = ((1 << f) + ep - 1) >> e;
        while (__builtin_clz(u) != __builtin_clz(v)) {
            (u > v ? u : v) >>= 1;
            ++k;
        }

        if (u != v)
            k += 2 * (__builtin_clz(1) - __builtin_clz(u ^ v) + 1);
    }

    std::cout << (k <= h ? "YES" : "NO") << '\n';

    return 0;
}
