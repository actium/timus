#include <iostream>

unsigned solve(unsigned m, unsigned n)
{
    if (m == 1)
        return (n + 1) / 2;

    if (n == 1)
        return (m + 1) / 2;

    return m % 3 == 0 || n % 3 == 0 ? 2 : 1;
}

int main()
{
    unsigned m, n;
    std::cin >> m >> n;

    std::cout << solve(m, n) << '\n';

    return 0;
}
