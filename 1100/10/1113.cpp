#include <iostream>

#include <cmath>

unsigned long long solve(unsigned n, unsigned m)
{
    double x = 0;
    unsigned i = 0;
    for (double d = m; x + d < n; d = m / double(2 * i + 1)) {
        x += d;
        ++i;
    }
    return std::ceil((2 * i + 1) * (n - x)) + i * m;
}

int main()
{
    unsigned n, m;
    std::cin >> n >> m;

    std::cout << solve(n, m) << '\n';

    return 0;
}
