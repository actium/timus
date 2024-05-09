#include <iostream>
#include <vector>

using graph_t = std::vector<std::vector<size_t>>;

bool paint(const graph_t& g, size_t u, unsigned k, std::vector<unsigned>& c)
{
    if (c[u] != ~0u)
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

    std::vector<unsigned> c(n, ~0u);
    for (size_t i = 0, k = 0; i < n; ++i) {
        if (c[i] != ~0u)
            continue;

        if (!paint(g, i, k, c)) {
            std::cout << "No solution" << '\n';
            return;
        }

        k += 2;
    }

    std::vector<unsigned> f(2 * n);
    for (const unsigned k : c)
        ++f[k];

    std::vector<std::vector<unsigned>> dp(1 + n, std::vector<unsigned>(1 + n, ~0u));
    dp[0][0] = 2 * n;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j <= n; ++j) {
            if (dp[i][j] != ~0u) {
                dp[i+1][j + f[2*i+0]] = 2 * i + 0;
                dp[i+1][j + f[2*i+1]] = 2 * i + 1;
            }
        }
    }

    size_t x = (n + 1) / 2;
    while (dp[n][x] == ~0u)
        --x;

    std::vector<unsigned> s(2 * n);
    for (size_t i = n; i > 0; x -= f[dp[i][x]], --i)
        s[dp[i][x]] = 1;

    std::vector<size_t> t[2];
    for (size_t i = 0; i < n; ++i)
        t[s[c[i]]].push_back(i);

    for (size_t i = 0; i < 2; ++i) {
        std::cout << t[i].size();
        for (const size_t x : t[i])
            std::cout << ' ' << 1+x;
        std::cout << '\n';
    }
}

int main()
{
    size_t n;
    std::cin >> n;

    graph_t g(n);
    for (size_t i = 0; i < n; ++i) {
        std::vector<bool> a(n);

        unsigned x;
        while (std::cin >> x && x != 0)
            a[x-1] = true;

        for (size_t j = 0; j < n; ++j) {
            if (j != i && !a[j]) {
                g[i].push_back(j);
                g[j].push_back(i);
            }
        }
    }

    solve(g);

    return 0;
}
