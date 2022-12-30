#include <iostream>
#include <queue>
#include <vector>

#include <cmath>

struct Point {
    double x;
    double y;
};

double operator -(const Point& t, const Point& s)
{
    return std::hypot(t.x - s.x, t.y - s.y);
}

int main()
{
    double v[2];
    std::cin >> v[0] >> v[1];

    size_t n;
    std::cin >> n;

    std::vector<Point> p(1 + n + 1);
    for (size_t i = 1; i <= n; ++i)
        std::cin >> p[i].x >> p[i].y;

    std::vector<std::vector<size_t>> g(1 + n + 1);
    for (unsigned u, v; std::cin >> u >> v && (u != 0 || v != 0); ) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    std::cin >> p.front().x >> p.front().y;
    std::cin >> p.back().x >> p.back().y;

    std::queue<size_t> q;
    std::vector<bool> f(1 + n + 1);

    const auto enqueue = [&](size_t u) {
        if (!f[u]) {
            q.push(u);
            f[u] = true;
        }
    };

    const auto dequeue = [&] {
        const size_t u = q.front();
        q.pop();
        f[u] = false;
        return u;
    };

    std::vector<std::pair<size_t, double>> d(1 + n + 1);
    for (size_t i = 1; i <= n + 1; ++i) {
        d[i].first = 0;
        d[i].second = (p[i] - p[0]) / v[0];
        enqueue(i);
    }

    while (!q.empty()) {
        const size_t u = dequeue();
        for (const size_t x : g[u]) {
            const double c = (p[x] - p[u]) / v[1];
            if (d[u].second + c < d[x].second) {
                d[x].first = u;
                d[x].second = d[u].second + c;
                enqueue(x);
            }
        }
        for (size_t x = 1; x <= n; ++x) {
            const double c = (p[x] - p[u]) / v[0];
            if (d[u].second + c < d[x].second) {
                d[x].first = u;
                d[x].second = d[u].second + c;
                enqueue(x);
            }
        }
    }

    for (size_t i = 1; i <= n; ++i) {
        const double c = (p.back() - p[i]) / v[0];
        if (d[i].second + c < d.back().second) {
            d.back().first = i;
            d.back().second = d[i].second + c;
        }
    }

    std::cout << std::fixed << d.back().second << '\n';

    std::vector<unsigned> r;
    for (unsigned u = d.back().first; u != 0; u = d[u].first)
        r.push_back(u);

    std::cout << r.size();
    for (auto it = r.rbegin(); it != r.rend(); ++it)
        std::cout << ' ' << *it;

    std::cout << '\n';

    return 0;
}
