#include <iostream>
#include <numeric>

unsigned solve(unsigned n)
{
    const unsigned b = n / 2;

    unsigned k = 0;
    for (unsigned i = 1; i <= b; ++i)
        k += (std::gcd(i, n) == 1);

    return k;
}

int main()
{
    unsigned n;
    std::cin >> n;

    std::cout << solve(n) << '\n';

    return 0;
}
