#include <algorithm>
#include <iostream>
#include <vector>

using graph_t = std::vector<std::vector<size_t>>;

unsigned solve(const graph_t& g, size_t u, size_t p)
{
    std::vector<unsigned> t;
    for (const size_t v : g[u]) {
        if (v != p)
            t.push_back(solve(g, v, u));
    }

    std::sort(t.begin(), t.end(), std::greater<unsigned>());

    unsigned d = 0;
    for (unsigned i = 0; i < t.size(); ++i)
        d = std::max(d, t[i] + i);

    return d + 1;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    graph_t g(n);
    for (size_t i = 0; i < n; ++i) {
        unsigned x;
        for (std::cin >> x; x-- != 0; std::cin >> x) {
            g[i].push_back(x);
            g[x].push_back(i);
        }
    }

    unsigned x;
    std::cin >> x;

    std::cout << solve(g, x-1, n) - 1 << '\n';

    return 0;
}
