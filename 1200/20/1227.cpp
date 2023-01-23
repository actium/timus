#include <iostream>
#include <vector>

struct Edge {
    size_t id;
    size_t s;
    size_t t;
    unsigned d;
};

using graph_t = std::vector<std::vector<size_t>>;

bool check(const graph_t& g, const std::vector<Edge>& e, size_t u, unsigned s, std::vector<bool>& v)
{
    const size_t n = g.size();

    v[u] = true;

    for (const size_t i : g[u]) {
        const Edge& p = e[i];
        if (v[n + p.id])
            continue;

        const size_t w = p.s ^ p.t ^ u;
        if (v[w] || p.d >= s)
            return true;

        v[n + p.id] = true;
        if (check(g, e, w, s - p.d, v))
            return true;

        v[n + p.id] = false;
    }

    v[u] = false;
    return false;
}

const char* solve(size_t n, const std::vector<Edge>& e, unsigned s)
{
    const size_t m = e.size();

    graph_t g(n);
    for (size_t i = 0; i < m; ++i) {
        g[e[i].s].push_back(i);
        g[e[i].t].push_back(i);
    }

    std::vector<bool> v(n + m);
    for (size_t i = 0; i < n; ++i) {
        if (check(g, e, i, s, v))
            return "YES";
    }
    return "NO";
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m;
    std::cin >> n >> m;

    unsigned s;
    std::cin >> s;

    std::vector<Edge> e(m);
    for (size_t i = 0; i < m; ++i) {
        e[i].id = i;
        std::cin >> e[i].s >> e[i].t >> e[i].d;
        --e[i].s, --e[i].t;
    }

    std::cout << solve(n, e, s) << '\n';

    return 0;
}
