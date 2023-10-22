#include <algorithm>
#include <iostream>
#include <vector>

using graph_t = std::vector<std::vector<size_t>>;

unsigned search(const graph_t& g, size_t u, size_t p)
{
    for (size_t v : g[u]) {
        if (v != p && search(g, v, u) == 0)
            return 1 + v;
    }
    return 0;
}

void solve(graph_t& g, size_t k)
{
    std::sort(g[k].begin(), g[k].end());

    const unsigned x = search(g, k, k);
    if (x != 0) {
        std::cout << "First player wins flying to airport " << x << '\n';
    } else {
        std::cout << "First player loses" << '\n';
    }
}

int main()
{
    size_t n;
    std::cin >> n;

    unsigned k;
    std::cin >> k;

    graph_t g(n);
    for (size_t i = 1; i < n; ++i) {
        unsigned u, v;
        std::cin >> u >> v;

        g[u-1].push_back(v-1);
        g[v-1].push_back(u-1);
    }

    solve(g, k - 1);

    return 0;
}
