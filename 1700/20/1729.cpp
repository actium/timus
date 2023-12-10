#include <iostream>

#include <cmath>

const long double pi = acosl(-1);

long double range(long double r, long double a)
{
    return r * sinl(2 * a) / sinl(pi / 2 - a);
}

int main()
{
    long double r, a;
    std::cin >> r >> a;

    a *= pi / 180;

    const unsigned q = (pi - a) / a;

    std::cout << std::fixed << r + q * range(r, a) + range(r, pi - (q + 1) * a) << '\n';

    return 0;
}
