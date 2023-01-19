#include <iostream>
#include <vector>

using branch_t = std::pair<size_t, unsigned>;
using tree_t = std::vector<std::vector<branch_t>>;

constexpr unsigned oo = ~0u;

unsigned traverse(const tree_t& t, size_t x, size_t p, std::vector<std::vector<unsigned>>& dp, unsigned q)
{
    unsigned k = 1;

    std::vector<size_t> b;
    for (const auto& e : t[x]) {
        if (e.first != p) {
            b.push_back(e.first);
            k += traverse(t, e.first, x, dp, e.second);
        }
    }

    dp[x][0] = 0;
    dp[x][1] = q;
    for (unsigned i = 2; i <= k; ++i) {
        switch (b.size()) {
            case 1:
                if (dp[b.front()][i-1] != oo)
                    dp[x][i] = q + dp[b.front()][i-1];
                break;

            case 2:
                for (unsigned j = 0; j < i; ++j) {
                    if (dp[b.front()][j] != oo && dp[b.back()][i-j-1] != oo)
                        dp[x][i] = std::max<int>(dp[x][i], q + dp[b.front()][j] + dp[b.back()][i-j-1]);
                }
                break;
        }
    }

    return k;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned n, q;
    std::cin >> n >> q;

    tree_t t(n);
    for (unsigned i = 1; i < n; ++i) {
        unsigned u, v, k;
        std::cin >> u >> v >> k;

        t[u-1].emplace_back(v-1, k);
        t[v-1].emplace_back(u-1, k);
    }

    std::vector<std::vector<unsigned>> dp(n, std::vector<unsigned>(n + 1, oo));
    traverse(t, 0, 0, dp, 0);
    std::cout << dp[0][q+1] << '\n';

    return 0;
}
