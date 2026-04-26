#include <algorithm>
#include <iostream>
#include <vector>

#include <cmath>

struct Point {
    int x;
    int y;
};

double solve(const std::vector<Point>& ps, unsigned k)
{
    const size_t n = ps.size();

    double best = 1e18;
    for (size_t i = 1; i < n; ++i) {
        for (size_t j = 0; j < i; ++j) {
            const long long dx = ps[i].x - ps[j].x, dy = ps[i].y - ps[j].y;
            const double length = std::hypot(dx, dy);

            std::vector<long long> cp(n);
            for (size_t q = 0; q < n; ++q)
                cp[q] = dx * (ps[q].y - ps[j].y) - dy * (ps[q].x - ps[j].x);

            std::sort(cp.begin(), cp.end());

            for (size_t l = 0; l + k <= n; ++l)
                best = std::min(best, double(cp[l+k-1] - cp[l]) / length);
        }
    }
    return std::max(best - 1, 0.0);
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    unsigned k;
    std::cin >> k;

    std::vector<Point> ps(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> ps[i].x >> ps[i].y;

    std::cout << std::fixed << (k == 1 ? 0 : solve(ps, k)) << '\n';

    return 0;
}
