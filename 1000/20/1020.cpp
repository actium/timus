#include <iostream>
#include <vector>

#define _USE_MATH_DEFINES
#include <cmath>

using point_t = std::pair<double, double>;

void solve(const std::vector<point_t>& p, double r)
{
    const size_t n = p.size();

    double d = 2 * M_PI * r;
    for (size_t i = 0; i < n; ++i) {
        const point_t p1 = p[i], p2 = p[(i+1)%n];

        d += std::hypot(p2.first - p1.first, p2.second - p1.second);
    }

    std::cout << std::fixed << d << '\n';
}

int main()
{
    size_t n;
    std::cin >> n;

    double r;
    std::cin >> r;

    std::vector<point_t> p(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> p[i].first >> p[i].second;

    solve(p, r);

    return 0;
}
