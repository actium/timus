#include <algorithm>
#include <iostream>
#include <vector>

struct Point {
    int x;
    int y;
};

std::istream& operator >>(std::istream& input_stream, Point& point)
{
    return input_stream >> point.x >> point.y;
}

double compute_x(const Point& s, const Point& t, int h)
{
    if (t.y == s.y)
        return s.x;

    const int dx = t.x - s.x, dy = t.y - s.y;
    return s.x + dx * double(h - s.y) / dy;
}

double solve(const std::vector<Point>& ps, const std::vector<Point>& qs, const std::vector<Point>& rs)
{
    auto mi = qs.begin();
    while (mi < qs.end() && mi->y < ps.begin()->y)
        ++mi;

    double w = rs[0].x - ps[0].x;
    for (auto li = ps.begin(), ri = rs.begin(); li != ps.end(); ) {
        const int h = std::min(li->y, ri->y);

        if (mi == qs.end() || mi->y > h) {
            const auto lx = (li != ps.begin() ? compute_x(*std::prev(li), *li, h) : li->x);
            const auto rx = (ri != rs.begin() ? compute_x(*std::prev(ri), *ri, h) : ri->x);
            w = std::min(w, rx - lx);
        }

        while (mi != qs.end() && mi->y <= h) {
            const auto lx = (li != ps.begin() ? compute_x(*std::prev(li), *li, mi->y) : li->x);
            const auto rx = (ri != rs.begin() ? compute_x(*std::prev(ri), *ri, mi->y) : ri->x);

            std::vector<int> xs;
            for (int y = mi->y; mi != qs.end() && mi->y == y; ++mi) {
                if (mi->x >= lx && mi->x <= rx)
                    xs.push_back(mi->x);
            }

            if (!xs.empty()) {
                std::sort(xs.begin(), xs.end());

                double cw = std::max(xs.front() - lx, rx - xs.back());
                for (size_t i = 1; i < xs.size(); ++i)
                    cw = std::max<double>(cw, xs[i] - xs[i-1]);

                w = std::min(w, cw);
            } else {
                w = std::min(w, rx - lx);
            }
        }

        li += (li->y == h);
        ri += (ri->y == h);
    }
    return w;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<Point> ps(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> ps[i];

    size_t m;
    std::cin >> m;

    std::vector<Point> rs(m);
    for (size_t i = 0; i < m; ++i)
        std::cin >> rs[i];

    size_t k;
    std::cin >> k;

    std::vector<Point> qs(k);
    for (size_t i = 0; i < k; ++i)
        std::cin >> qs[i];

    std::cout << std::fixed << solve(ps, qs, rs) << '\n';

    return 0;
}
