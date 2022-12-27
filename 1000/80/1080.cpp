#include <iostream>
#include <vector>

using graph_t = std::vector<std::vector<size_t>>;

bool paint(const graph_t& g, size_t v, int t, std::vector<int>& c)
{
    if (c[v] != 0)
        return c[v] == t;

    c[v] = t;

    for (const size_t u : g[v]) {
        if (!paint(g, u, t ^ 1, c))
            return false;
    }
    return true;
}

void solve(const graph_t& g)
{
    const size_t n = g.size();

    std::vector<int> c(n);
    for (size_t i = 0; i < n; ++i) {
        if (c[i] != 0)
            continue;

        if (!paint(g, i, 2, c)) {
            std::cout << -1 << '\n';
            return;
        }
    }

    for (size_t i = 0; i < n; ++i)
        std::cout << c[i] - 2;

    std::cout << '\n';
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n;
    std::cin >> n;

    graph_t g(n);
    for (size_t i = 0; i < n; ++i) {
        unsigned x;
        for (std::cin >> x; x != 0; std::cin >> x) {
            g[i].push_back(x - 1);
            g[x-1].push_back(i);
        }
    }

    solve(g);

    return 0;
}
