#include <iostream>
#include <vector>

void solve(unsigned n)
{
    constexpr unsigned oo = 1000000000;

    std::vector<unsigned> dp(1 + n, oo);
    dp[0] = 0;
    for (unsigned i = 0; i < n; ++i) {
        for (unsigned j = 1; i + j * j <= n; ++j)
            dp[i + j * j] = std::min(dp[i + j * j], dp[i] + 1);
    }

    std::cout << dp[n] << '\n';
}

int main()
{
    unsigned n;
    std::cin >> n;

    solve(n);

    return 0;
}
