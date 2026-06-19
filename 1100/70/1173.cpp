#include <algorithm>
#include <iostream>
#include <vector>

#include <cmath>

struct Point {
    unsigned id;

    long long x;
    long long y;
};

long long cross_product(const Point& s, const Point& t)
{
    return s.x * t.y - s.y * t.x;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    double sx, sy;
    std::cin >> sx >> sy;

    size_t n;
    std::cin >> n;

    std::vector<Point> ps(n);
    for (size_t i = 0; i < n; ++i) {
        double x, y;
        std::cin >> x >> y >> ps[i].id;

        ps[i].x = std::round((x - sx) * 1000);
        ps[i].y = std::round((y - sy) * 1000);
    }

    std::sort(ps.begin(), ps.end(), [](const Point& lhs, const Point& rhs) {
        return std::atan2(lhs.y, lhs.x) < std::atan2(rhs.y, rhs.x);
    });

    size_t x = 1;
    while (x < n && cross_product(ps[x-1], ps[x]) >= 0)
        ++x;

    std::cout << 0 << '\n';
    for (size_t i = 0; i < n; ++i)
        std::cout << ps[x++%n].id << '\n';
    std::cout << 0 << '\n';

    return 0;
}
