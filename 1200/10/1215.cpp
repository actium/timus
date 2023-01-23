#include <iostream>
#include <vector>

#include <cmath>

struct Point {
    int x;
    int y;
};

int cross_product(const Point& a, const Point& b, const Point& c)
{
    return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
}

int dot_product(const Point& a, const Point& b, const Point& c)
{
    return (c.x - a.x) * (b.x - a.x) + (c.y - a.y) * (b.y - a.y);
}

double solve(const std::vector<Point>& p, const Point& x)
{
    const size_t n = p.size(), oo = 1e9;

    double r = oo;
    for (size_t i = 0; i < n; ++i) {
        const Point& a = p[(n+i-1)%n];
        const Point& b = p[i];
        if (cross_product(a, b, x) <= 0)
            continue;

        const int t = dot_product(a, b, x);
        if (t < 0) {
            r = std::min(r, std::hypot(x.x - a.x, x.y - a.y));
            continue;
        }

        const double dx = b.x - a.x, dy = b.y - a.y;
        if (t > dx * dx + dy * dy) {
            r = std::min(r, std::hypot(x.x - b.x, x.y - b.y));
            continue;
        }

        const double px = a.x + t * dx / (dx * dx + dy * dy);
        const double py = a.y + t * dy / (dx * dx + dy * dy);
        r = std::min(r, std::hypot(x.x - px, x.y - py));
    }
    return r == oo ? 0 : 2 * r;
}

int main()
{
    Point x;
    std::cin >> x.x >> x.y;

    size_t n;
    std::cin >> n;

    std::vector<Point> p(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> p[i].x >> p[i].y;

    std::cout << std::fixed << solve(p, x) << '\n';

    return 0;
}
