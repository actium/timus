#include <algorithm>
#include <iostream>
#include <vector>

#define _USE_MATH_DEFINES
#include <cmath>

struct Point {
    int x;
    int y;
};

bool operator <(const Point& a, const Point& b)
{
    return std::make_pair(a.x, a.y) < std::make_pair(b.x, b.y);
}

bool operator !=(const Point& a, const Point& b)
{
    return a.x != b.x || a.y != b.y;
}

int cross_product(const Point& a, const Point& b, const Point& c)
{
    return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
}

unsigned norm(const Point& a, const Point& b)
{
    const int dx = a.x - b.x, dy = a.y - b.y;
    return dx * dx + dy * dy;
}

int main()
{
    unsigned n, d;
    std::cin >> n >> d;

    std::vector<Point> p(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> p[i].x >> p[i].y;

    const size_t x = std::min_element(p.begin(), p.end()) - p.begin();

    std::vector<size_t> c;
    for (size_t i = 0; i < n; ++i) {
        if (p[i] != p[x])
            c.push_back(i);
    }

    std::sort(c.begin(), c.end(), [&](size_t i, size_t j) {
        const auto cp = cross_product(p[i], p[j], p[x]);
        return cp != 0 ? cp > 0 : norm(p[i], p[x]) < norm(p[j], p[x]);
    });

    std::vector<size_t> hull(1, x);
    for (const size_t i : c) {
        while (hull.size() > 1 && cross_product(p[hull.end()[-2]], p[hull.end()[-1]], p[i]) <= 0)
            hull.pop_back();

        hull.push_back(i);
    }
    hull.push_back(hull[0]);

    double s = 2 * M_PI * d;
    for (size_t i = 1; i < hull.size(); ++i)
        s += std::hypot(p[hull[i]].x - p[hull[i-1]].x, p[hull[i]].y - p[hull[i-1]].y);

    std::cout << std::round(s) << '\n';

    return 0;
}
