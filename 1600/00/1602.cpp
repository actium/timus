#include <iostream>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, k;
    std::cin >> n >> k;

    double u, v;
    std::cin >> u >> v;

    const unsigned su = u * 100 + 0.5, sv = v * 100 + 0.5;

    unsigned t[100] = { (k - 1) * sv + 1500, (n - 1) * su };
    for (unsigned i = 2; i <= n; ++i)
        t[i] = std::max(t[0], (n - i) * su) + (i - 1) * sv * 2 + 500;

    unsigned x = 1;
    for (unsigned i = 2; i <= n; ++i) {
        if (t[i] <= t[x])
            x = i;
    }

    std::cout << x << '\n';

    return 0;
}
