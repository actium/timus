#include <iomanip>
#include <iostream>
#include <vector>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned a1, b1, a2, b2;
    std::cin >> a1 >> b1 >> a2 >> b2;

    unsigned n, m;
    std::cin >> n >> m;

    const auto t = a1 * n + b1 * m;
    const auto k = (a2 * n + b2 * m) / 2.0;

    const auto evaluate = [=](double p, double q) {
        if (q > k)
            return t - p;

        if (q < k)
            return p;

        return std::max(p, t - p);
    };

    std::pair<double, std::pair<double, double>> best = { evaluate(0, 0), { 0, 0 } };
    for (const auto& [x, y] : { std::make_pair(0u, 0u), std::make_pair(0u, m), std::make_pair(n, 0u), std::make_pair(n, m) })
        best = std::max(best, { evaluate(a1 * x + b1 * y, a2 * x + b2 * y), std::make_pair(x, y) });

    std::vector<std::pair<double, double>> c;

    const auto intersect = [&](double x, double y) {
        if (x >= 0 && x <= n && y >= 0 && y <= m)
            c.emplace_back(x, y);
    };

    if (a2 != 0) {
        intersect(k / a2, 0);
        intersect((k - b2 * m) / a2, m);
    }
    if (b2 != 0) {
        intersect(0, k / b2);
        intersect(n, (k - a2 * n) / b2);
    }

    for (const auto& [x, y] : c) {
        const double p = a1 * x + b1 * y, u = std::max(p, t - p);
        best = std::max(best, std::make_pair(u, std::make_pair(x, y)));
    }

    std::cout << std::fixed << std::setprecision(10) << best.second.first << ' ' << best.second.second << '\n';

    return 0;
}
