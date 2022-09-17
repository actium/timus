#include <iostream>
#include <vector>

int main()
{
    using integer = unsigned long long;

    unsigned n;
    std::cin >> n;

    std::vector<std::vector<integer>> dp(1+n, std::vector<integer>(1+n));
    for (unsigned h = 0; h <= n; ++h)
        dp[0][h] = 1;

    for (unsigned c = 1; c <= n; ++c) {
        for (unsigned h = 1; h <= c; ++h)
            dp[c][h] = dp[c][h-1] + dp[c-h][h-1];

        for (unsigned h = c + 1; h <= n; ++h)
            dp[c][h] = dp[c][h-1];
    }

    std::cout << dp[n][n] - 1 << '\n';

    return 0;
}
