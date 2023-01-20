#include <iostream>
#include <queue>
#include <vector>

using graph_t = std::vector<std::vector<size_t>>;

void compute_distances(const graph_t& g, size_t s, std::vector<std::pair<unsigned, size_t>>& d)
{
    const size_t n = g.size();

    std::queue<size_t> q;
    std::vector<bool> p(n);

    const auto enqueue = [&](size_t v, size_t u, unsigned w) {
        if (!p[v]) {
            d[v].first = w;
            d[v].second = u;
            q.push(v);
            p[v] = true;
        }
    };

    const auto dequeue = [&] {
        const size_t v = q.front();
        q.pop();
        return v;
    };

    enqueue(s, s, 0);
    while (!q.empty()) {
        const size_t v = dequeue();
        for (const size_t u : g[v])
            enqueue(u, v, d[v].first + 1);
    }
}

size_t farthest(const std::vector<std::pair<unsigned, size_t>>& d)
{
    const size_t n = d.size();

    size_t x = 0;
    for (size_t i = 1; i < n; ++i) {
        if (d[i].first > d[x].first)
            x = i;
    }
    return x;
}

void compute_jumps(const std::vector<std::pair<unsigned, size_t>>& d, std::vector<std::vector<size_t>>& jt)
{
    const size_t n = d.size(), h = jt.size();

    for (size_t i = 0; i < n; ++i)
        jt[0][i] = d[i].second;

    for (size_t i = 1; i < h; ++i) {
        for (size_t j = 0; j < n; ++j)
            jt[i][j] = jt[i-1][jt[i-1][j]];
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n, q;
    std::cin >> n >> q;

    graph_t g(n);
    for (size_t i = 1; i < n; ++i) {
        unsigned u, v;
        std::cin >> u >> v;

        g[u-1].push_back(v-1);
        g[v-1].push_back(u-1);
    }

    std::vector<std::pair<unsigned, size_t>> d0(n);
    compute_distances(g, 0, d0);

    const size_t s = farthest(d0);
    std::vector<std::pair<unsigned, size_t>> d1(n);
    compute_distances(g, s, d1);

    const size_t t = farthest(d1);
    std::vector<std::pair<unsigned, size_t>> d2(n);
    compute_distances(g, t, d2);

    const size_t h = __builtin_clz(1) - __builtin_clz(n) + 1;

    std::vector<std::vector<size_t>> jt1(h, std::vector<size_t>(n));
    compute_jumps(d1, jt1);

    std::vector<std::vector<size_t>> jt2(h, std::vector<size_t>(n));
    compute_jumps(d2, jt2);

    const auto query = [&](size_t v, unsigned d) -> unsigned {
        if (d > d1[v].first && d > d2[v].first)
            return 0;

        const auto& jt = (d1[v].first > d2[v].first ? jt1 : jt2);
        while (d > 0) {
            const unsigned h = __builtin_clz(1) - __builtin_clz(d);
            v = jt[h][v];
            d -= 1 << h;
        }
        return 1 + v;
    };

    for (size_t i = 0; i < q; ++i) {
        unsigned v, d;
        std::cin >> v >> d;

        std::cout << query(v - 1, d) << '\n';
    }

    return 0;
}
