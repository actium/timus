#include <iostream>
#include <vector>

using graph_t = std::vector<std::vector<std::pair<size_t, unsigned>>>;

unsigned traverse(const graph_t& g, const std::vector<unsigned>& a, size_t u, size_t p, unsigned h, std::vector<unsigned>& v)
{
    v[u] = h + a[u];

    unsigned s = a[u];
    for (const std::pair<size_t, unsigned>& e : g[u]) {
        if (e.first == p)
            continue;

        const unsigned y = traverse(g, a, e.first, u, v[u] + e.second, v);
        s = std::max(s, y + e.second + a[u]);
        v[u] = std::max(v[u], s);
    }
    return s;
}

bool print_path(const graph_t& g, const std::vector<unsigned>& a, size_t u, size_t p, unsigned h, size_t k, unsigned t)
{
    if (h + a[u] == t) {
        std::cout << k << '\n';
        std::cout << 1 + u;
        return true;
    }

    for (const std::pair<size_t, unsigned>& e : g[u]) {
        if (e.first != p && print_path(g, a, e.first, u, h + a[u] + e.second, k + 1, t)) {
            std::cout << ' ' << 1 + u;
            return true;
        }
    }
    return false;
}

void solve(const graph_t& g, const std::vector<unsigned>& a)
{
    const size_t n = g.size();

    std::vector<unsigned> v(n);
    for (size_t i = 0; i < n; ++i) {
        if (v[i] == 0)
            traverse(g, a, i, i, 0, v);
     }

    size_t s = 0;
    for (size_t i = 1; i < n; ++i) {
        if (v[i] > v[s])
            s = i;
    }

    std::cout << v[s] << '\n';
    print_path(g, a, s, s, 0, 1, v[s]);
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, k;
    std::cin >> n >> k;

    std::vector<unsigned> a(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> a[i];

    graph_t g(n);
    for (size_t i = 0; i < k; ++i) {
        unsigned u, v, c;
        std::cin >> u >> v >> c;

        g[u-1].emplace_back(v-1, c);
        g[v-1].emplace_back(u-1, c);
    }

    solve(g, a);

    return 0;
}
