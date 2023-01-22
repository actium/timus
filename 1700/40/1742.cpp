#include <iostream>
#include <vector>

using graph_t = std::vector<std::pair<size_t, size_t>>;

unsigned traverse(const graph_t& g, size_t u, std::vector<unsigned>& t, unsigned p)
{
    const size_t v = g[u].second, n = g.size();
    if (v != n && t[v] == 0) {
        t[u] = p;
        p = traverse(g, v, t, p + 1);
    }

    if (v != n)
        p = std::min(p, t[v]);

    t[u] = ~0u;
    return p;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    graph_t g(n, std::make_pair(n, n));
    for (size_t i = 0; i < n; ++i) {
        unsigned p;
        std::cin >> p;

        if (--p != i) {
            g[p].first = i;
            g[i].second = p;
        }
    }

    unsigned lb = 0, ub = 0;
    {
        std::vector<unsigned> t(n);
        for (size_t i = 0; i < n; ++i) {
            if (g[i].first == n) {
                ++lb;
                ub += traverse(g, i, t, 1);
            }
        }
        for (size_t i = 0; i < n; ++i) {
            if (t[i] == 0) {
                ++lb;
                ++ub;
                traverse(g, i, t, 1);
            }
        }
    }

    std::cout << lb << ' ' << ub << '\n';

    return 0;
}
