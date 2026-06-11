#include <iostream>
#include <vector>

#include <cmath>

const double epsilon = 1e-9;
const double pi = std::acos(-1);

struct Point {
    double x;
    double y;
};

double distance(const Point& s, const Point& t)
{
    const auto dx = t.x - s.x, dy = t.y - s.y;
    return std::hypot(dx, dy);
}

const char* solve(const std::vector<Point>& ps)
{
    const size_t n = ps.size();

    Point center = { 0, 0 };
    for (const auto& p : ps) {
        center.x += p.x;
        center.y += p.y;
    }
    center.x /= n;
    center.y /= n;

    const auto r = distance(center, ps[0]);
    for (const auto& p : ps) {
        const auto d = distance(center, p);
        if (d + epsilon < r || r + epsilon < d)
            return "NO";
    }

    const auto x = 2 * r * std::sin(pi / n);
    for (size_t i = 0; i < n; ++i) {
        const auto d = distance(ps[i], ps[(i + 1) % n]);
        if (d + epsilon < x || x + epsilon < d)
            return "NO";
    }

    return "YES";
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<Point> ps(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> ps[i].x >> ps[i].y;

    std::cout << solve(ps) << '\n';

    return 0;
}
