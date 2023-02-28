#include <iostream>
#include <vector>

using graph_t = std::vector<std::vector<size_t>>;

constexpr unsigned UNDEFINED = ~0u;

bool paint(const graph_t& g, size_t u, unsigned k, std::vector<unsigned>& c)
{
    if (c[u] != UNDEFINED)
        return c[u] == k;

    c[u] = k;

    for (const size_t v : g[u]) {
        if (!paint(g, v, k ^ 1, c))
            return false;
    }

    return true;
}

void solve(const graph_t& g)
{
    const size_t n = g.size();

    std::vector<unsigned> c(n, UNDEFINED);
    for (size_t i = 0, k = 0; i < n; ++i) {
        if (c[i] != UNDEFINED)
            continue;

        if (!paint(g, i, k, c)) {
            std::cout << "IMPOSSIBLE" << '\n';
            return;
        }

        k += 2;
    }

    std::vector<unsigned> f(2 * n);
    for (const unsigned k : c)
        ++f[k];

    std::vector<std::vector<unsigned>> dp(1 + n, std::vector<unsigned>(1 + n / 2, UNDEFINED));
    dp[0][0] = 2 * n;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j <= n / 2; ++j) {
            if (dp[i][j] == UNDEFINED)
                continue;

            if (j + f[2 * i + 0] <= n / 2)
                dp[i + 1][j + f[2 * i + 0]] = 2 * i + 0;

            if (j + f[2 * i + 1] <= n / 2)
                dp[i + 1][j + f[2 * i + 1]] = 2 * i + 1;
        }
    }

    if (dp[n][n/2] == UNDEFINED) {
        std::cout << "IMPOSSIBLE" << '\n';
        return;
    }

    std::vector<unsigned> s(2 * n);
    for (size_t i = n, j = n / 2; i > 0; j -= f[dp[i][j]], --i)
        s[dp[i][j]] = 1;

    std::vector<unsigned> v[2];
    for (size_t i = 0; i < n; ++i)
        v[s[c[i]]].push_back(1 + i);

    for (size_t i = 0; i < 2; ++i) {
        for (const unsigned x : v[i])
            std::cout << x << ' ';

        std::cout << '\n';
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m;
    std::cin >> n >> m;

    graph_t g(2 * n);
    for (size_t i = 0; i < m; ++i) {
        unsigned u, v;
        std::cin >> u >> v;

        g[u-1].push_back(v-1);
        g[v-1].push_back(u-1);
    }

    solve(g);

    return 0;
}
