#include <iostream>

struct Point {
    int x;
    int y;
    int z = 0;
};

std::istream& operator >>(std::istream& input, Point& p)
{
    return input >> p.x >> p.y;
}

bool test(const Point& p0, const Point& p1, const Point& p2, const Point& p3, unsigned r)
{
    const double a = p1.y * (p2.z - p3.z) + p2.y * (p3.z - p1.z) + p3.y * (p1.z - p2.z);
    const double b = p1.z * (p2.x - p3.x) + p2.z * (p3.x - p1.x) + p3.z * (p1.x - p2.x);
    const double c = p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y);
    const double d = p1.x * (p2.y * p3.z - p3.y * p2.z) + p2.x * (p3.y * p1.z - p1.y * p3.z) + p3.x * (p1.y * p2.z - p2.y * p1.z);
    const double e = a * p0.x + b * p0.y + c * p0.z - d;

    return r * r * (a * a + b * b + c * c) >= e * e;
}

bool solve(Point p[4], unsigned m, unsigned h)
{
    if (m < h)
        return false;

    if (m >= 2 * h)
        return true;

    p[0].z = h;
    return test(p[0], p[1], p[2], p[4], m - h) || test(p[0], p[1], p[3], p[4], m - h) || test(p[0], p[2], p[3], p[4], m - h);
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    Point p[5];

    unsigned m, h;
    std::cin >> m >> h >> p[4].z;

    for (size_t i = 0; i < 5; ++i)
        std::cin >> p[i];

    std::cout << (solve(p, m, h) ? "YES" : "NO") << '\n';

    return 0;
}
