#include <iostream>

#include <cmath>

struct Point {
    double x;
    double y;
    double z;

    Point(double x, double y, double z)
        : x(x), y(y), z(z)
    {}
};

double operator -(const Point& lhs, const Point& rhs)
{
    const double dx = lhs.x - rhs.x, dy = lhs.y - rhs.y, dz = lhs.z - rhs.z;

    return sqrt(dx * dx + dy * dy + dz * dz);
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned a, b, c;
    std::cin >> a >> b >> c;

    double x1, y1;
    std::cin >> x1 >> y1;

    double x2, y2;
    std::cin >> x2 >> y2;

    const auto p = [=](double x, double y) -> Point {
        if (x < c)
            return Point(0, x, y - (b + c));

        if (x > c + a)
            return Point(a, (c + a + c) - x, y - (b + c));

        if (y < b)
            return Point(x - c, 0, b - y);

        if (y < b + c)
            return Point(x - c, y - b, 0);

        if (y < b + c + b)
            return Point(x - c, c, y - (b + c));

        return Point(x - c, (b + c + b + c) - y, b);
    };

    std::cout << std::fixed << p(x1, y1) - p(x2, y2) << '\n';

    return 0;
}
