#include <iostream>

int main()
{
    unsigned n;
    std::cin >> n;

    unsigned dp[45][3] = {};
    dp[0][0] = dp[0][1] = 1;
    for (size_t i = 1; i < n; ++i) {
        dp[i][0] = dp[i-1][1] + dp[i-1][2] / 2;
        dp[i][1] = dp[i-1][0] + dp[i-1][2] / 2;
        dp[i][2] = dp[i-1][0] + dp[i-1][1];
    }

    std::cout << dp[n-1][0] + dp[n-1][1] << '\n';

    return 0;
}
