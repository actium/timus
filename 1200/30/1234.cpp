#include <iostream>

#include <cmath>

const char* solve(unsigned a, unsigned b, unsigned c, unsigned d, unsigned e)
{
    if (a > b)
        std::swap(a, b);
    if (b > c)
        std::swap(b, c);
    if (a > b)
        std::swap(a, b);

    if (d > e)
        std::swap(d, e);

    if (a <= d && b <= e)
        return "YES";

    if (b > e && d * (b * b + a * a) >= 2 * b * a * e + (b * b - a * a) * sqrt(b * b + a * a - e * e))
        return "YES";

    return "NO";
}

int main()
{
    double a, b, c, d, e;
    std::cin >> a >> b >> c >> d >> e;

    std::cout <<solve(a * 10 + 0.5, b * 10 + 0.5, c * 10 + 0.5, d * 10 + 0.5, e * 10 + 0.5) << '\n';

    return 0;
}
