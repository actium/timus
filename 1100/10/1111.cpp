#include <algorithm>
#include <iostream>
#include <vector>

#include <cmath>

struct Point {
    double x;
    double y;
};

double distance(const std::pair<Point, Point>& s, const Point& p)
{
    const Point corners[4] = {
        s.first,
        {
            (s.first.x + s.second.x - s.first.y + s.second.y) / 2,
            (s.first.y + s.second.y + s.first.x - s.second.x) / 2,
        },
        s.second,
        {
            (s.first.x + s.second.x + s.first.y - s.second.y) / 2,
            (s.first.y + s.second.y - s.first.x + s.second.x) / 2,
        },
    };

    std::vector<double> d;
    for (size_t i = 0; i < 4; ++i) {
        const size_t j = (i + 1) % 4;

        const double cp = (corners[j].x - corners[i].x) * (p.y - corners[i].y) - (corners[j].y - corners[i].y) * (p.x - corners[i].x);
        if (cp > 0)
            continue;

        const double dp1 = (corners[j].x - corners[i].x) * (p.x - corners[j].x) + (corners[j].y - corners[i].y) * (p.y - corners[j].y);
        if (dp1 > 0) {
            d.push_back(hypot(p.x - corners[j].x, p.y - corners[j].y));
            continue;
        }

        const double dp2 = (corners[j].x - corners[i].x) * (p.x - corners[i].x) + (corners[j].y - corners[i].y) * (p.y - corners[i].y);
        if (dp2 < 0) {
            d.push_back(hypot(p.x - corners[i].x, p.y - corners[i].y));
            continue;
        }

        d.push_back(-cp / hypot(corners[j].x - corners[i].x, corners[j].y - corners[i].y));
    }

    return d.empty() ? 0 : *std::min_element(d.begin(), d.end());
}

int main()
{
    size_t n;
    std::cin >> n;

    std::vector<std::pair<Point, Point>> s(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> s[i].first.x >> s[i].first.y >> s[i].second.x >> s[i].second.y;

    Point p;
    std::cin >> p.x >> p.y;

    std::vector<double> d(n);
    for (size_t i = 0; i < n; ++i)
        d[i] = distance(s[i], p);

    std::vector<size_t> x(n);
    for (size_t i = 0; i < n; ++i)
        x[i] = i;

    std::sort(x.begin(), x.end(), [&](size_t i, size_t j) {
        if (d[i] != d[j])
            return d[i] < d[j];

        return i < j;
    });

    for (const size_t i : x)
        std::cout << 1 + i << ' ';

    return 0;
}
