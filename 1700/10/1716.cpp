#include <iostream>
#include <vector>

int main()
{
    unsigned n, s;
    std::cin >> n >> s;

    const unsigned k = s - 2 * n;

    std::vector<std::vector<double>> dp(2, std::vector<double>(1 + k));
    dp[1][1] = 1;
    for (unsigned i = 1; i < n; ++i) {
        std::vector<std::vector<double>> ndp(2, std::vector<double>(1 + k));
        for (unsigned j = 0; j <= i + 1 && j <= k; ++j) {
            if (j != 0)
                ndp[1][j] = (dp[0][j-1] * (i - j + 1) + (dp[1][j-1] + 1) * (j - 1)) / i;

            ndp[0][j] = ((dp[0][j] + 1) * (i - j) + dp[1][j] * j) / i;
        }
        dp.swap(ndp);
    }

    std::cout << std::fixed << n - (dp[0][k] * (n - k) + dp[1][k] * k) / n << '\n';

    return 0;
}
