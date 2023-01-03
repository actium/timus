#include <iostream>

unsigned count(unsigned n, unsigned d)
{
    unsigned k = 0;
    for (unsigned m = 1; m <= n; m *= 10) {
        const unsigned a = n / m, b = n % m, z = a % 10;
        k += a / 10 * m;
        if (z > d)
            k += m;
        if (z == d)
            k += b + 1;
        if (d == 0)
            k -= m;
    }
    return k;
}

int main()
{
    unsigned n;
    std::cin >> n;

    for (unsigned d = 0; d <= 9; ++d)
        std::cout << count(n, d) << '\n';

    return 0;
}
