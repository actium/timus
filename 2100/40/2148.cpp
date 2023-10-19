#include <iostream>

#include <cmath>

struct Point {
    double x;
    double y;
};

struct Circle {
    Point center;
    double radius;
};

void solve(const Circle& c, const Point& s, const Point& t)
{
    const double dx = (s.x + t.x) / 2 - c.center.x, dy = (s.y + t.y) / 2 - c.center.y, d = dx * dx + dy * dy;
    if (d <= c.radius * c.radius) {
        std::cout << "No way" << '\n';
    } else {
        std::cout << std::fixed << c.center.x + dx * c.radius / sqrt(d) << ' ' << c.center.y + dy * c.radius / sqrt(d) << '\n';
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    Circle c;
    std::cin >> c.center.x >> c.center.y >> c.radius;

    Point s;
    std::cin >> s.x >> s.y;

    Point t;
    std::cin >> t.x >> t.y;

    solve(c, s, t);

    return 0;
}
