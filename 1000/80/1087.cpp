#include <iostream>
#include <vector>

int main()
{
    unsigned n, m;
    std::cin >> n >> m;

    std::vector<unsigned> k(m);
    for (unsigned i = 0; i < m; ++i)
        std::cin >> k[i];

    // dp[i] = winner of i-stone game
    // if a player wins i-stone game, then he must lose (i + k[j])-stone one
    std::vector<unsigned> dp(1 + n, 2);
    dp[0] = 1;
    for (unsigned i = 1; i <= n; ++i) {
        for (unsigned j = 0; j < m; ++j) {
            if (k[j] <= i && dp[i - k[j]] == 2)
                dp[i] = 1;
        }
    }

    std::cout << dp[n] << '\n';

    return 0;
}
