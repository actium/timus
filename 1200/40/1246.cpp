#include <iostream>
#include <vector>

#define _USE_MATH_DEFINES
#include <cmath>

struct Point {
    int x;
    int y;
};

void solve(const std::vector<Point>& ps)
{
    const size_t n = ps.size();

    double s = 0;
    for (size_t i = 0; i < n; ++i) {
        const size_t last = (n + i - 1) % n, next = (i + 1) % n;

        const long long dx1 = ps[last].x - ps[i].x, dy1 = ps[last].y - ps[i].y;
        const long long dx2 = ps[next].x - ps[i].x, dy2 = ps[next].y - ps[i].y;

        const auto cp = dx1 * dy2 - dx2 * dy1, dp = dx1 * dx2 + dy1 * dy2;

        double a = atan2(cp, dp);
        if (a < 0)
            a += 2 * M_PI;

        s += a;
    }

    std::cout << (std::abs(M_PI * (n + 2) - s) < std::abs(M_PI * (n - 2) - s) ? "ccw" : "cw") << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<Point> ps(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> ps[i].x >> ps[i].y;

    solve(ps);

    return 0;
}
