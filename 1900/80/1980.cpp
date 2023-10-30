#include <iostream>
#include <limits>
#include <set>
#include <vector>

struct Edge {
    size_t u;
    size_t v;

    unsigned d;
    unsigned s;
};

using graph_t = std::vector<std::vector<size_t>>;

double check(const std::vector<Edge>& edges, const graph_t& g, double d, std::vector<size_t>& p)
{
    const size_t n = g.size();

    std::set<std::pair<double, size_t>> q;
    std::vector<double> t(n, std::numeric_limits<double>::infinity());

    const auto enqueue = [&](size_t v, size_t e, double dt) {
        if (dt < t[v]) {
            q.emplace(dt, v);
            t[v] = dt;
            p[v] = e;
        }
    };

    enqueue(0, 0, 0);
    while (!q.empty()) {
        const std::pair<double, size_t> x = *q.begin();
        q.erase(q.begin());

        if (x.first != t[x.second])
            continue;

        for (const size_t i : g[x.second]) {
            const Edge& e = edges[i];
            enqueue(e.v, i, x.first + e.d / (e.s + d));
        }
    }

    return t.back();
}

void solve(const std::vector<Edge>& edges, const graph_t& g, unsigned t)
{
    const size_t n = g.size();

    std::vector<size_t> p(n);

    double lb = 0, ub = (n - 1) * 1000.0;
    while (std::abs(ub - lb) > 1e-6) {
        const double mid = (lb + ub) / 2;
        (check(edges, g, mid, p) > t ? lb : ub) = mid;
    }

    std::vector<size_t> path;
    for (size_t x = n - 1; x != 0; x = edges[path.back()].u)
        path.push_back(p[x]);

    std::cout << std::fixed << ub << ' ' << path.size() << '\n';
    for (auto it = path.rbegin(); it != path.rend(); ++it)
        std::cout << 1 + *it / 2 << ' ';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m;
    std::cin >> n >> m;

    std::vector<Edge> edges(2 * m);

    graph_t g(n);
    for (size_t i = 0; i < m; ++i) {
        unsigned a, b, s, l;
        std::cin >> a >> b >> s >> l;

        edges[2 * i + 0] = { a-1, b-1, l, s };
        edges[2 * i + 1] = { b-1, a-1, l, s };

        g[a-1].push_back(2 * i + 0);
        g[b-1].push_back(2 * i + 1);
    }

    unsigned t;
    std::cin >> t;

    solve(edges, g, t);

    return 0;
}
