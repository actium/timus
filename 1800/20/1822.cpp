#include <algorithm>
#include <iostream>
#include <vector>

struct Node {
    unsigned p;
    unsigned t;
};

double solve(const std::vector<Node>& g, unsigned tl)
{
    const size_t n = g.size();

    std::vector<unsigned> d(n);
    for (size_t i = 1; i < n; ++i)
        ++d[g[i].p - 1];

    std::vector<size_t> q;
    for (size_t i = 0; i < n; ++i) {
        if (d[i] == 0)
            q.push_back(i);
    }
    for (size_t i = 0; i < q.size() && q[i] != 0; ++i) {
        const size_t x = q[i];
        if (--d[g[x].p - 1] == 0)
            q.push_back(g[x].p - 1);
    }

    const auto check = [&](double x) {
        std::vector<std::vector<unsigned>> t(n);
        for (const size_t i : q) {
            std::sort(t[i].begin(), t[i].end());

            unsigned d = 0;
            for (size_t j = 0; j * 100 < t[i].size() * x; ++j)
                d = std::max(d, t[i][j]);

            if (i == 0)
                return d <= tl;

            const size_t p = g[i].p - 1;
            t[p].push_back(d + g[i].t);
        }
        return false;
    };

    double lb = 0, ub = 100;
    while (std::abs(ub - lb) > 1e-4) {
        const double mid = (lb + ub) / 2;
        (check(mid) ? lb : ub) = mid;
    }

    return lb;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    unsigned t;
    std::cin >> t;

    std::vector<Node> g(n);
    for (size_t i = 1; i < n; ++i)
        std::cin >> g[i].p >> g[i].t;

    std::cout << std::fixed << solve(g, t) << '\n';

    return 0;
}
