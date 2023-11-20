#include <iomanip>
#include <iostream>

#include <cmath>

struct Point {
    double x;
    double y;
};

double distance(const Point& p1, const Point& p2)
{
    return std::hypot(p1.x - p2.x, p1.y - p2.y);
}

bool solve(const Point& a, const Point& b, const Point& c, Point& s, Point& t)
{
    const double ab = distance(a, b), bc = distance(b, c), ca = distance(c, a), p = ab + bc + ca;

    const double d = p * p - 8 * bc * ca;
    if (d < 0)
        return false;

    const auto check = [&](double ct) {
        const double sc = bc * ca / (2 * ct);
        if (ct <= bc + 1e-9 && sc <= ca + 1e-9) {
            s = { c.x + (a.x - c.x) * sc / ca, c.y + (a.y - c.y) * sc / ca };
            t = { c.x + (b.x - c.x) * ct / bc, c.y + (b.y - c.y) * ct / bc };
            return true;
        }
        return false;
    };

    return check((p + std::sqrt(d)) / 4) || check((p - std::sqrt(d)) / 4);
}

int main()
{
    Point a, b, c;
    std::cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;

    Point s, t;
    solve(a, b, c, s, t) || solve(b, c, a, s, t) || solve(c, a, b, s, t);

    std::cout << "YES" << '\n';
    std::cout << std::fixed << std::setprecision(9) << s.x << ' ' << s.y << '\n';
    std::cout << std::fixed << std::setprecision(9) << t.x << ' ' << t.y << '\n';

    return 0;
}
