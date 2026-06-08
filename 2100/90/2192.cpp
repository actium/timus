#include <iostream>
#include <vector>

constexpr unsigned oo = ~0u;

struct Edge {
    unsigned v;
    unsigned s;
    unsigned w;
};

using graph_t = std::vector<std::vector<Edge>>;

bool is_greater(std::pair<unsigned, unsigned> lhs, std::pair<unsigned, unsigned> rhs)
{
    return 1ull * lhs.first * rhs.second > 1ull * rhs.first * lhs.second;
}

void search(const graph_t& g, unsigned u, std::vector<std::pair<unsigned, unsigned>>& dp)
{
    dp[u].second = 1;

    for (const auto& e : g[u]) {
        if (dp[e.v].second == 0)
            search(g, e.v, dp);

        std::pair<unsigned, unsigned> c = dp[e.v];
        if (is_greater(c, std::make_pair(e.s, e.w)))
            c = std::make_pair(e.s, e.w);

        if (is_greater(c, dp[u]))
            dp[u] = c;
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m, q;
    std::cin >> n >> m >> q;

    graph_t g(1+n);
    for (size_t i = 0; i < m; ++i) {
        unsigned u, v, s, w;
        std::cin >> u >> v >> s >> w;

        g[u].push_back({ v, s, w });
    }

    std::vector<std::pair<unsigned, unsigned>> dp(1+n);
    dp[n] = std::make_pair(oo, 1);
    search(g, 1, dp);

    for (size_t i = 0; i < q; ++i) {
        unsigned a, b;
        std::cin >> a >> b;

        std::cout << (is_greater(dp[1], std::make_pair(b, a)) ? "YES" : "NO") << '\n';
    }

    return 0;
}
