#include <algorithm>
#include <iostream>
#include <vector>

#include <cassert>

using graph_t = std::vector<std::vector<unsigned>>;

void paint(graph_t& g, unsigned u, std::vector<unsigned>& f, std::vector<unsigned>& t)
{
    while (!g[u].empty()) {
        const unsigned v = g[u].back();
        g[u].pop_back();

        const auto it = std::find(g[v].begin(), g[v].end(), u);
        assert(it != g[v].end());
        *it = g[v].back();
        g[v].pop_back();

        paint(g, v, f, t);
    }

    if (const unsigned v = f[u]; v != 0) {
        f[u] = 0;
        f[v] = 0;

        paint(g, v, f, t);
        t.push_back(0);
    }

    t.push_back(u);
}

void solve(graph_t& g)
{
    const size_t n = g.size();

    std::vector<unsigned> f(n);
    {
        std::vector<unsigned> p;
        for (unsigned i = 1; i < n; ++i) {
            if (g[i].size() % 2 == 0)
                continue;

            if (p.empty()) {
                p.push_back(i);
            } else {
                f[i] = p.back();
                f[p.back()] = i;
                p.pop_back();
            }
        }

        assert(p.empty());
    }

    unsigned s = 1;
    for (unsigned i = 1; i < n; ++i) {
        if (f[i] != 0)
            s = i;
    }

    std::vector<unsigned> t;
    paint(g, s, f, t);
    t.push_back(0);

    std::vector<std::vector<unsigned>> trails(1);
    for (const unsigned x : t) {
        if (x == 0 && trails.back().size() > 1)
            trails.emplace_back();

        if (x == 0)
            trails.back().clear();
        else
            trails.back().push_back(x);
    }
    trails.pop_back();

    std::cout << trails.size() << '\n';
    for (const auto& e : trails) {
        for (const auto x : e)
            std::cout << x << ' ';
        std::cout << '\n';
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m;
    std::cin >> n >> m;

    graph_t g(1+n);
    for (size_t i = 0; i < m; ++i) {
        unsigned u, v;
        std::cin >> u >> v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    solve(g);

    return 0;
}
