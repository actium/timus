#include <iostream>

int main()
{
    using integer = unsigned long long;

    unsigned n, a, b;
    std::cin >> n >> a >> b;

    const unsigned k = std::max(a, b);

    integer dp[1+20][1+15] = {};
    for (unsigned i = 0; i <= k; ++i)
        dp[0][i] = 1;

    for (unsigned i = 1; i <= n; ++i) {
        dp[i][0] = 1;

        for (unsigned j = 1; j <= k; ++j)
            dp[i][j] = dp[i][j-1] + dp[i-1][j];
    }

    std::cout << dp[n][a] * dp[n][b] << '\n';

    return 0;
}
