#include <iostream>
#include <vector>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, k;
    std::cin >> n >> k;

    std::vector<std::vector<unsigned>> c(n, std::vector<unsigned>(n));
    for (size_t i = 1; i < n; ++i) {
        for (size_t j = i; j < n; ++j)
            std::cin >> c[i][j];
    }

    for (size_t i = 1; i < n; ++i) {
        for (size_t j = 1; j < n; ++j)
            c[i][j] += c[i-1][j] + c[i][j-1] - c[i-1][j-1];
    }

    using state_t = std::pair<unsigned, size_t>;

    std::vector<std::vector<state_t>> dp(1 + k, std::vector<state_t>(n));
    for (size_t i = 1; i <= k; ++i) {
        for (size_t l = n - 1; l > 0; --l) {
            for (size_t r = l; r < n; ++r) {
                const unsigned q = dp[i-1][r].first + c[l][r] - c[l][l-1];
                if (q > dp[i][l-1].first) {
                    dp[i][l-1].first = q;
                    dp[i][l-1].second = r;
                }
            }
        }
    }

    size_t x = 0;
    for (size_t i = 1; i < n; ++i) {
        if (dp[k][i].first > dp[k][x].first)
            x = i;
    }

    std::cout << dp[k][x].first << '\n';
    for (size_t i = k; i > 0; --i) {
        std::cout << 1 + x << ' ';
        x = dp[i][x].second;
    }

    return 0;
}
