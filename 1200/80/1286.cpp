#include <iostream>
#include <numeric>

using integer = long long;
using point_t = std::pair<integer, integer>;

bool solve(integer p, integer q, const point_t& s, const point_t& t)
{
    const integer dx = t.first - s.first, dy = t.second - s.second;
    if (dx == 0 && dy == 0)
        return true;

    if (p == 0 && q == 0)
        return false;

    const integer d = std::gcd(p, q);
    if (dx % d != 0 || dy % d != 0)
        return false;

    return p / d % 2 + q / d % 2 == 1 || (dx + dy) / d % 2 == 0;
}

int main()
{
    integer p, q;
    std::cin >> p >> q;

    point_t s;
    std::cin >> s.first >> s.second;

    point_t t;
    std::cin >> t.first >> t.second;

    std::cout << (solve(p, q, s, t) ? "YES" : "NO") << '\n';

    return 0;
}
