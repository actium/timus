#include <iostream>
#include <vector>

#include <cmath>

struct Point {
    unsigned x;
    unsigned y;
};

void solve(const std::vector<Point>& p)
{
    const size_t n = p.size();

    const auto colinear = [&p](size_t i, size_t j, size_t k) {
        const int dx1 = p[i].x - p[j].x, dy1 = p[i].y - p[j].y;
        const int dx2 = p[i].x - p[k].x, dy2 = p[i].y - p[k].y;
        return dx1 * dy2 == dx2 * dy1;
    };

    const auto distance = [&p](size_t i, size_t j) {
        const int dx = p[i].x - p[j].x, dy = p[i].y - p[j].y;
        return std::hypot(dx, dy);
    };

    double d = 0;

    std::vector<std::vector<bool>> v(n, std::vector<bool>(n));
    for (size_t i = 1; i < n; ++i) {
        for (size_t j = 0; j < i; ++j) {
            if (v[i][j])
                continue;

            std::vector<size_t> c = { i, j };
            for (size_t k = 0; k < n; ++k) {
                if (k != j && k != i && colinear(i, j, k))
                    c.push_back(k);
            }

            double r = 0;
            for (const size_t i : c) {
                for (const size_t j : c) {
                    r = std::max(r, distance(i, j));
                    v[i][j] = true;
                }
            }
            d += r;
        }
    }

    std::cout << static_cast<int>(std::round(d)) << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<Point> p(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> p[i].x >> p[i].y;

    solve(p);

    return 0;
}
