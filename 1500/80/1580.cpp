#include <iostream>
#include <vector>

using graph_t = std::vector<std::vector<std::pair<size_t, int>>>;

constexpr int oo = 2000000000;

struct State {
    int t;
    int d;
    int x;
    bool v;
};

int search(const graph_t& g, size_t u, size_t p, std::vector<State>& states, int t, int d)
{
    if (states[u].t != 0)
        return states[u].t != t ? (states[u].d - d) * t : oo;

    states[u].t = t;
    states[u].d = d;

    for (const auto& e : g[u]) {
        if (e.first == p)
            continue;

        const int x = search(g, e.first, u, states, -t, e.second - d);
        if (x != oo)
            return x;
    }
    return oo;
}

bool assign(const graph_t& g, size_t u, size_t p, int x, std::vector<State>& states)
{
    if (states[u].v)
        return states[u].x == x;

    states[u].x = x;
    states[u].v = true;

    for (const auto& e : g[u]) {
        if (e.first != p && !assign(g, e.first, u, 2 * e.second - x, states))
            return false;
    }
    return true;
}

void solve(const graph_t& g)
{
    const size_t n = g.size();

    std::vector<State> states(n);
    for (size_t i = 0; i < n; ++i) {
        if (states[i].v)
            continue;

        const int x = search(g, i, i, states, 1, 0);
        if (x == oo || !assign(g, i, i, x, states)) {
            std::cout << "IMPOSSIBLE" << '\n';
            return;
        }
    }

    for (const auto& s : states)
        std::cout << std::fixed << s.x / 2.0 << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m;
    std::cin >> n >> m;

    graph_t g(n);
    for (size_t i = 0; i < m; ++i) {
        unsigned u, v;
        std::cin >> u >> v;

        int a;
        std::cin >> a;

        g[u-1].emplace_back(v-1, a);
        g[v-1].emplace_back(u-1, a);
    }

    solve(g);

    return 0;
}
