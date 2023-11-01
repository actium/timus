#include <iostream>
#include <queue>
#include <vector>

struct Edge {
    unsigned v;
    unsigned t;
    unsigned w;
};

using graph_t = std::vector<std::vector<Edge>>;

unsigned search(const graph_t& g, unsigned w)
{
    const size_t n = g.size();

    using state_t = std::pair<unsigned, size_t>;

    std::priority_queue<state_t, std::vector<state_t>, std::greater<state_t>> q;
    std::vector<unsigned> d(n, ~0u);

    const auto enqueue = [&](size_t u, unsigned t) {
        if (d[u] > t) {
            q.emplace(t, u);
            d[u] = t;
        }
    };

    enqueue(0, 0);
    while (!q.empty() && q.top().second != n - 1) {
        const std::pair<unsigned, size_t> p = q.top();
        q.pop();

        if (p.first > d[p.second])
            continue;

        for (const Edge& e : g[p.second]) {
            if (e.w >= w)
                enqueue(e.v, p.first + e.t);
        }
    }

    return d[n-1];
}

unsigned solve(const graph_t& g)
{
    unsigned lb = 0, ub = 10000001;
    while (lb + 1 < ub) {
        const unsigned mid = (lb + ub) / 2;
        (search(g, mid * 100 + 3000000) <= 1440 ? lb : ub) = mid;
    }
    return lb;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m;
    std::cin >> n >> m;

    graph_t g(n);
    for (size_t i = 0; i < m; ++i) {
        unsigned u, v, t, w;
        std::cin >> u >> v >> t >> w;

        g[u-1].push_back({ v-1, t, w });
        g[v-1].push_back({ u-1, t, w });
    }

    std::cout << solve(g) << '\n';

    return 0;
}
