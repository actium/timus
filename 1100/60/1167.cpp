#include <iostream>
#include <vector>

int main()
{
    constexpr unsigned oo = ~0u >> 1;

    size_t n, k;
    std::cin >> n >> k;

    std::vector<unsigned> c(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> c[i];

    std::vector<std::vector<unsigned>> dp(1+k, std::vector<unsigned>(1+n, oo));
    dp[0][0] = 0;
    for (size_t i = 1; i <= k; ++i) {
        for (size_t j = i-1; j < n; ++j) {
            unsigned f[2] = {};
            for (size_t q = 1; j + q <= n; ++q) {
                ++f[c[j+q-1]];

                dp[i][j+q] = std::min(dp[i][j+q], dp[i-1][j] + f[0] * f[1]);
            }
        }
    }

    std::cout << dp[k][n] << '\n';

    return 0;
}
