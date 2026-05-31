#include <iostream>

#include <cmath>

struct Point {
    int x;
    int y;
};

std::istream& operator >>(std::istream& input, Point& point)
{
    return input >> point.x >> point.y;
}

double select_x(Point s, Point t)
{
    if (s.y == t.y)
        return (s.x + t.x) / 2.0;

    if (s.x == t.x)
        return s.x - sqrt(s.y * t.y);

    const auto d = hypot(t.x - s.x, t.y - s.y);
    return (s.x * t.y - t.x * s.y + (s.x < t.x ? 1 : -1) * d * sqrt(s.y * t.y)) / (t.y - s.y);
}

double solve(Point s, Point t)
{
    if (s.y * t.y <= 0)
        return acos(-1);

    s.y = abs(s.y);
    t.y = abs(t.y);

    const auto x = select_x(s, t);
    return std::abs(atan2(s.y, s.x - x) - atan2(t.y, t.x - x));
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    Point s, t;
    std::cin >> s >> t;

    std::cout << std::fixed << solve(s, t) << '\n';

    return 0;
}
