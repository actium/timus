#include <algorithm>
#include <iostream>
#include <vector>

#include <cmath>

struct Point {
    int x;
    int y;
};

unsigned count(const std::vector<Point>& p, const std::vector<std::vector<double>>& d, size_t q, unsigned r)
{
    const size_t n = p.size();

    std::vector<std::pair<double, bool>> angles;
    for (size_t i = 0; i < n; ++i) {
        if (i == q || d[i][q] > 2 * r)
            continue;

        const double a = std::atan2(p[i].y - p[q].y, p[i].x - p[q].x), b = std::acos(d[i][q] / (2 * r));
        angles.emplace_back(a - b, false);
        angles.emplace_back(a + b, true);
    }

    std::sort(angles.begin(), angles.end());

    unsigned k = 1, v = 1;
    for (auto it = angles.begin(); it != angles.end(); ++it) {
        k += (it->second ? -1 : 1);
        v = std::max(v, k);
    }
    return v;
}

unsigned solve(const std::vector<Point>& p, unsigned dr, unsigned cr)
{
    const size_t n = p.size();

    if (dr < cr)
        return 0;

    std::vector<std::vector<double>> distances(n, std::vector<double>(n));
    for (size_t i = 1; i < n; ++i) {
        for (size_t j = 0; j < i; ++j) {
            distances[i][j] = std::hypot(p[i].x - p[j].x, p[i].y - p[j].y);
            distances[j][i] = distances[i][j];
        }
    }

    unsigned k = 0;
    for (size_t i = 0; i < n; ++i)
        k = std::max(k, count(p, distances, i, dr - cr));

    return k;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<Point> p(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> p[i].x >> p[i].y;

    unsigned dr, cr;
    std::cin >> dr >> cr;

    std::cout << solve(p, dr, cr) << '\n';

    return 0;
}
