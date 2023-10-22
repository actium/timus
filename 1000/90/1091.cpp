#include <iostream>

using integer = long long;

constexpr int factors[] = { 0, 1, 1, 0, 1, -1, 1, 0, 0, -1, 1, 0, 1, -1, -1, 0, 1, 0, 1, 0, -1, -1, 1, 0, 0 };

integer C(unsigned k, unsigned n)
{
    integer v = 1;
    for (unsigned i = std::max(k, n - k) + 1; i <= n; ++i)
        v *= i;
    for (unsigned i = 2; i <= std::min(k, n - k); ++i)
        v /= i;

    return v;
}

unsigned solve(unsigned k, unsigned s)
{
    integer q = 0;
    for (unsigned i = 2; i <= s / k; ++i)
        q += factors[i-1] * C(k, s / i);

    return std::min<integer>(q, 10000);
}

int main()
{
    unsigned k, s;
    std::cin >> k >> s;

    std::cout << solve(k, s) << '\n';

    return 0;
}
