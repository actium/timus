#include <iostream>
#include <vector>

#include <cmath>

const double pi = acos(-1);

struct Point {
    double x;
    double y;
};

double solve(const std::vector<Point>& ps)
{
    const size_t n = ps.size();

    std::vector<std::vector<double>> distances(n, std::vector<double>(n));
    std::vector<double> min_distances(n, 50);
    for (size_t i = 1; i < n; ++i) {
        for (size_t j = 0; j < i; ++j) {
            const double dx = ps[i].x - ps[j].x, dy = ps[i].y - ps[j].y;

            distances[i][j] = hypot(dx, dy);
            distances[j][i] = distances[i][j];

            min_distances[i] = std::min(min_distances[i], distances[i][j]);
            min_distances[j] = std::min(min_distances[j], distances[j][i]);
        }
    }

    double v = 0;
    for (size_t i = 1; i < n; ++i) {
        if (min_distances[i] < 1)
            continue;

        for (size_t j = 0; j < i; ++j) {
            if (min_distances[j] < 1)
                continue;

             if (min_distances[i] + min_distances[j] <= distances[i][j]) {
                v = std::max(v, pi * (min_distances[i] * min_distances[i] + min_distances[j] * min_distances[j]));
            } else {
                const double r1 = std::max(1.0, distances[i][j] - std::max(min_distances[i], min_distances[j]));
                const double r2 = distances[i][j] - r1;
                v = std::max(v, pi * (r1 * r1 + r2 * r2));
            }
        }
    }
    return v;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<Point> ps(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> ps[i].x >> ps[i].y;

    std::cout << std::fixed << solve(ps) << '\n';

    return 0;
}
