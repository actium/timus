#include <iostream>

int main()
{
    unsigned n;
    std::cin >> n;

    unsigned dp[56] = { 0, 1, 1 };
    for (unsigned i = 3; i <= n; ++i)
        dp[i] += dp[i-1] + dp[i-3] + 1;

    std::cout << dp[n] << '\n';

    return 0;
}
