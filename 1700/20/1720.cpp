#include <iostream>

using integer = unsigned long long;

integer count(integer a, integer b, integer ub)
{
    if (ub < a)
        return 0;

    if (a == 1)
        return ub;

    const auto q = ub / a, r = ub % a;

    const auto d = b - a;
    if (d == 0)
        return q;

    const auto s = (a + d - 2) / d;
    const auto k = std::min(q, s) - 1;
    const auto e = std::min(q * d, r);

    integer t = 1 + std::min(e, a - 1) + d * k * (k + 1) / 2 + k;
    if (q > s)
        t += (q - s) * a;

    return t;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    integer a, b, lb, ub;
    std::cin >> a >> b >> lb >> ub;

    std::cout << count(a, b, ub) - count(a, b, lb-1) << '\n';

    return 0;
}
