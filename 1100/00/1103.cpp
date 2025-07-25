#include <algorithm>
#include <iostream>
#include <vector>

struct Point {
    int x;
    int y;
};

bool operator !=(const Point& lhs, const Point& rhs)
{
    return lhs.x != rhs.x || lhs.y != rhs.y;
}

struct Vector {
    int dx;
    int dy;
};

Vector operator -(const Point& lhs, const Point& rhs)
{
    return { lhs.x - rhs.x, lhs.y - rhs.y };
}

long long cross_product(const Vector& u, const Vector& v)
{
    return 1LL * u.dx * v.dy - 1LL * u.dy * v.dx;
}

bool is_inside_circle(const Point& a, const Point& b, const Point& c, const Point& d) {
    const __int128_t ax = a.x - d.x, ay = a.y - d.y;
    const __int128_t bx = b.x - d.x, by = b.y - d.y;
    const __int128_t cx = c.x - d.x, cy = c.y - d.y;

    const __int128_t dot_a = ax * ax + ay * ay;
    const __int128_t dot_b = bx * bx + by * by;
    const __int128_t dot_c = cx * cx + cy * cy;

    return ax * (by * dot_c - cy * dot_b) - ay * (bx * dot_c - cx * dot_b) + dot_a * (bx * cy - cx * by) > 0;
}

std::vector<Point> solve(const std::vector<Point>& ps)
{
    const size_t n = ps.size(), m = n - 1;

    std::vector<Point> s(m);
    for (size_t i = 0; i < n; i++) {
        const Point& pa = ps[i];

        std::copy_if(ps.begin(), ps.end(), s.begin(), [&](const Point& p) {
            return p != pa;
        });

        std::sort(s.begin(), s.end(), [&](const Point& lhs, const Point& rhs) {
            const Vector u = lhs - pa, v = rhs - pa;

            const bool lhs_is_upper = u.dy > 0 || u.dy == 0 && u.dx > 0;
            const bool rhs_is_upper = v.dy > 0 || v.dy == 0 && v.dx > 0;

            return lhs_is_upper != rhs_is_upper ? lhs_is_upper : cross_product(u, v) > 0;
        });

        for (size_t j = 0; j < m; ++j) {
            Point pb = s[j];
            Point pc = s[(j + m / 2) % m];

            if (cross_product(pb - pa, pc - pa) < 0)
                std::swap(pb, pc);

            unsigned count = 0;
            for (size_t k = 0; k < m; ++k) {
                if (k != j && is_inside_circle(pa, pb, pc, s[k]))
                    ++count;
            }

            if (2 * count == n - 3)
                return { pa, pb, pc };
        }
    }
    return {};
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<Point> ps(n);
    for (size_t i = 0; i < n; i++)
        std::cin >> ps[i].x >> ps[i].y;

    for (const Point& p : solve(ps))
        std::cout << p.x << ' ' << p.y << '\n';

    return 0;
}
