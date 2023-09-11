#include <iostream>
#include <string>
#include <vector>

using Graph = std::vector<std::vector<unsigned>>;

void traverse(const Graph& g, unsigned u, unsigned p, std::vector<unsigned>& dp, unsigned& d)
{
    for (const unsigned v : g[u]) {
        if (v == p)
            continue;

        traverse(g, v, u, dp, d);

        d = std::max(d, dp[u] + dp[v] + 1);
        dp[u] = std::max(dp[u], dp[v] + 1);
    }
}

unsigned solve(const Graph& g)
{
    unsigned d = 0;
    {
        std::vector<unsigned> dp(g.size());
        traverse(g, 0, 0, dp, d);
    }
    return d;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, m, k = 0;
    std::cin >> m >> n >> std::ws;

    std::vector<std::string> a(n);
    for (unsigned i = 0; i < n; ++i)
        std::getline(std::cin, a[i]);

    std::vector<std::vector<unsigned>> x(n, std::vector<unsigned>(m));
    for (unsigned i = 0; i < n; ++i) {
        for (unsigned j = 0; j < m; ++j) {
            if (a[i][j] == '.')
                x[i][j] = k++;
        }
    }

    Graph g(k);

    const auto add_edge = [&](unsigned p, unsigned q) {
        g[p].push_back(q);
        g[q].push_back(p);
    };

    for (unsigned i = 0; i < n; ++i) {
        for (unsigned j = 0; j < m; ++j) {
            if (a[i][j] == '#')
                continue;

            if (i > 0 && a[i-1][j] == '.')
                add_edge(x[i][j], x[i-1][j]);

            if (j > 0 && a[i][j-1] == '.')
                add_edge(x[i][j], x[i][j-1]);
        }
    }

    std::cout << solve(g) << '\n';

    return 0;
}
