#include <iostream>
#include <vector>

using edge_t = std::pair<unsigned, unsigned>;
using graph_t = std::vector<std::vector<edge_t>>;

bool check(const graph_t& g, size_t u, unsigned mask, unsigned& v)
{
    if (u == 1)
        return true;

    v |= 1 << u;

    for (const edge_t& e : g[u]) {
        if ((v & 1 << e.first) == 0 && (mask & e.second) != 0 && check(g, e.first, mask, v))
            return true;
    }
    return false;
}

unsigned scan(const graph_t& g, unsigned k, unsigned c)
{
    const auto first = [](unsigned c) {
        return (1 << c) - 1;
    };

    const auto next = [](unsigned v) {
        const unsigned a = (v | (v - 1)) + 1;
        const unsigned b = 1 << __builtin_ctz(a) - __builtin_ctz(v) - 1;
        return a | (b - 1);
    };

    const unsigned mask = first(k);
    for (unsigned o = first(c), i = o; i >= o; i = next(i) & mask) {
        unsigned v = 0;
        if (check(g, 0, i, v))
            return i;
    }
    return 0;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t k, n, m;
    std::cin >> k >> n >> m;

    graph_t g(n);
    for (size_t i = 0; i < m; ++i) {
        unsigned u, v, c;
        std::cin >> u >> v >> c;

        g[u].emplace_back(v, 1 << c);
        g[v].emplace_back(u, 1 << c);
    }

    unsigned lb = 0, ub = k, v = (1 << k) - 1;
    while (lb + 1 < ub) {
        const unsigned mid = (lb + ub) / 2;

        const unsigned c = scan(g, k, mid);
        if (c != 0 && __builtin_popcount(c) < __builtin_popcount(v))
            v = c;

        (c == 0 ? lb : ub) = mid;
    }

    std::cout << __builtin_popcount(v) << '\n';
    for (size_t i = 0; i < k; ++i) {
        if ((v & 1 << i) != 0)
            std::cout << i << ' ';
    }

    return 0;
}
