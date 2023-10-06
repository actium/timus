#include <iostream>

struct Point {
    int x;
    int y;
};

int dot(const Point& a, const Point& b, const Point& c)
{
    return (b.x - a.x) * (c.x - b.x) + (b.y - a.y) * (c.y - b.y);
}

unsigned solve(const Point c[4])
{
    unsigned k = 0;
    for (size_t i0 = 0; i0 < 4; ++i0) {
        const size_t i1 = (i0 + 1) % 4, i2 = (i0 + 2) % 4, i3 = (i0 + 3) % 4;

        const Point p1 = { (c[i0].x + c[i1].x) / 2, (c[i0].y + c[i1].y) / 2 };
        const Point p2 = { (c[i2].x + c[i3].x) / 2, (c[i2].y + c[i3].y) / 2 };
        const Point p3 = { (c[i1].x + c[i3].x) / 2, (c[i1].y + c[i3].y) / 2 };

        if (dot(c[i0], p1, p2) == 0 && dot(c[i1], p1, p2) == 0 && dot(c[i2], p2, p1) == 0 && dot(c[i3], p2, p1) == 0)
            ++k;

        if (dot(c[i0], p3, c[i1]) == 0 && dot(c[i2], p3, c[i3]) == 0)
            ++k;
    }
    return k;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    Point c[4];
    for (size_t i = 0; i < 4; ++i) {
        std::cin >> c[i].x >> c[i].y;

        c[i].x *= 2, c[i].y *= 2;
    }

    std::cout << solve(c) << '\n';

    return 0;
}
