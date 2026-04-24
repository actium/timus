#include <iostream>

struct Point {
    unsigned x;
    unsigned y;
};

std::istream& operator >>(std::istream& input, Point& p)
{
    return input >> p.x >> p.y;
}

unsigned distance(const Point& s, const Point& t)
{
    const unsigned dx = std::max(s.x, t.x) - std::min(s.x, t.x);
    const unsigned dy = std::max(s.y, t.y) - std::min(s.y, t.y);
    return dx + dy;
}

unsigned solve(unsigned n, unsigned m, unsigned k, Point s, Point t)
{
    unsigned d = 0;

    const auto check = [&](const Point& p, const Point& q, unsigned e) {
        if (p.x < 1 || p.x > n || p.y < 1 || p.y > m)
            return;

        if (q.x < 1 || q.x > n || q.y < 1 || q.y > m)
            return;

        const unsigned d1 = distance(s, p), d2 = distance(p, q);
        if (d1 + d2 + e <= k)
            d = std::max(d, d2 + 1);
    };

    for (unsigned x = 1; x <= n; ++x) {
        check({ x, t.y-1 }, { t.x, t.y-1 }, 0);

        if (x < t.x && (s.x < t.x || m != 1))
            check({ x, t.y }, { t.x-1, t.y }, s.x < t.x ? 0 : 2);
        if (t.x < x && (t.x < s.x || m != 1))
            check({ x, t.y }, { t.x+1, t.y }, t.x < s.x ? 0 : 2);

        check({ x, t.y+1 }, { t.x, t.y+1 }, 0);
    }

    for (unsigned y = 1; y <= m; ++y) {
        check({ t.x-1, y }, { t.x-1, t.y }, 0);

        if (y < t.y && (s.y < t.y || n != 1))
            check({ t.x, y }, { t.x, t.y-1 }, s.y < t.y ? 0 : 2);
        if (t.y < y && (t.y < s.y || n != 1))
            check({ t.x, y }, { t.x, t.y+1 }, t.y < s.y ? 0 : 2);

        check({ t.x+1, y }, { t.x+1, t.y }, 0);
    }

    return d;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, m, k;
    std::cin >> n >> m >> k;

    Point s, t;
    std::cin >> s >> t;

    std::cout << solve(n, m, k, s, t) << '\n';

    return 0;
}
