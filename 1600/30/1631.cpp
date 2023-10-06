#include <iomanip>
#include <iostream>

#include <cmath>

double solve(unsigned n, unsigned m)
{
    const unsigned k = n + m + 1;

    return k * sqrt(2) + n * m - k;
}

int main()
{
    unsigned n, m;
    std::cin >> n >> m;

    std::cout << std::setprecision(9) << std::fixed << solve(n, m) << '\n';

    return 0;
}
