#include <iostream>
#include <vector>

#include <cmath>

struct Point {
    double x;
    double y;
};

double solve(const std::vector<Point>& ps)
{
    const size_t n = ps.size();

    const auto d = [&](size_t i, size_t j) {
        return std::hypot(ps[i%n].x - ps[j%n].x, ps[i%n].y - ps[j%n].y);
    };

    std::vector<std::vector<double>> dp1(n, std::vector<double>(n)), dp2(n, std::vector<double>(n));
    for (size_t i = 1; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            dp1[j][i] = std::min(dp1[j][i-1] + d(j+i, j+i-1), dp2[j][i-1] + d(j, j+i));
            dp2[j][i] = std::min(dp2[(j+1)%n][i-1] + d(j, j+1), dp1[(j+1)%n][i-1] + d(j, j+i));
        }
    }

    double v = std::min(dp1[0][n-1], dp2[0][n-1]);
    for (size_t i = 1; i < n; ++i) {
        const double u = std::min(dp1[i][n-1], dp2[i][n-1]);
        v = std::min(v, u);
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
