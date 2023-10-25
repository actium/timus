#include <iostream>
#include <vector>

using graph_t = std::vector<std::vector<size_t>>;

void traverse(const graph_t& g, size_t u, size_t p, std::vector<unsigned>& dp, unsigned& d)
{
    for (const size_t v : g[u]) {
        if (v == p)
            continue;

        traverse(g, v, u, dp, d);

        d = std::max(d, dp[u] + dp[v] + 1);
        dp[u] = std::max(dp[u], dp[v] + 1);
    }
}

void solve(const graph_t& g)
{
    const size_t n = g.size();

    std::vector<unsigned> dp(n);
    unsigned d = 0;
    traverse(g, 0, 0, dp, d);

    std::vector<size_t> centroids;
    for (size_t i = 0; i < n; ++i) {
        if (dp[i] == d / 2 || dp[i] == (d + 1) / 2)
            centroids.push_back(i);
    }

    if (centroids.size() == 2 && centroids[0] > centroids[1])
        std::swap(centroids[0], centroids[1]);

    for (const size_t x : centroids)
        std::cout << 1 + x << ' ';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    graph_t g(n);
    for (size_t i = 1; i < n; ++i) {
        unsigned p;
        std::cin >> p;

        g[p-1].push_back(i);
        g[i].push_back(p-1);
    }

    solve(g);

    return 0;
}
