#include <iostream>

constexpr unsigned M = 136;

unsigned t[M];

int solve(unsigned n)
{
    if (n == 0)
        return 0;

    if (n == 1 || n == 2)
        return 1;

    if (t[n] == 0) {
        bool v[256] = {};
        v[solve(n - 2)] = true;
        for (unsigned i = 2; i < n; ++i)
            v[solve(i - 2) ^ solve(n - i - 1)] = true;

        while (v[t[n]++]);
    }
    return t[n] - 1;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    std::cout << (solve(n % M) == 0 ? "Black" : "White") << '\n';

    return 0;
}
