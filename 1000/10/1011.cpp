#include <iostream>

#include <cmath>

unsigned solve(unsigned p, unsigned q)
{
    unsigned x  = 1;
    while (p * x >= 10000 * std::ceil(q * x / 10000.0 - 1))
        ++x;

    return x;
}

int main()
{
    double p, q;
    std::cin >> p >> q;

    std::cout << solve(std::round(p * 100), std::round(q * 100)) << '\n';

    return 0;
}
