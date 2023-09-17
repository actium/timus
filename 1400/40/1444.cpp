#include <algorithm>
#include <iostream>
#include <vector>

#include <cmath>

struct Point {
    int x;
    int y;

    size_t i;
    double a;
};

int main()
{
    size_t n;
    std::cin >> n;

    std::vector<Point> p(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> p[i].x >> p[i].y;

        p[i].i = i;
    }

    for (int i = n - 1; i >= 0; --i) {
        p[i].x -= p[0].x;
        p[i].y -= p[0].y;
        p[i].a = atan2(p[i].y, p[i].x);
    }

    std::sort(p.begin() + 1, p.end(), [](const Point& a, const Point& b) {
        if (a.x * b.y == a.y * b.x && a.x * b.x + a.y * b.y >= 0)
            return a.x * a.x + a.y * a.y < b.x * b.x + b.y * b.y;

        return a.a < b.a;
    });

    size_t x = 1;
    for (size_t i = 1; i < n; ++i) {
        const int dx1 = p[i-1].x - p[0].x, dy1 = p[i-1].y - p[0].y;
        const int dx2 = p[i].x - p[0].x, dy2 = p[i].y - p[0].y;

        const int dp = dx1 * dx2 + dy1 * dy2, cp = dx1 * dy2 - dy1 * dx2;
        if (cp < 0 || cp == 0 && dp < 0) {
            x = i;
            break;
        }
    }

    std::cout << n << '\n';
    std::cout << 1 << '\n';
    for (size_t i = 1; i < n; ++i) {
        const size_t j = (x + i - 1) % n;
        std::cout << 1 + p[j + (j < x)].i << '\n';
    }

    return 0;
}
