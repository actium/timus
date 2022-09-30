#include <iostream>
#include <vector>

int main()
{
    unsigned n, s;
    std::cin >> n >> s;

    std::vector<unsigned> dp(1+n);
    dp[s] = 1;
    for (unsigned i = s; i < n; ++i) {
        if (dp[i] == 0)
            continue;

        for (unsigned p = 1; p <= 100; ++p) {
            if (i * p % 100 == 0) {
                const unsigned x = i + i * p / 100;
                if (x <= n)
                    dp[x] = std::max(dp[x], dp[i] + 1);
            }
        }
    }

    unsigned k = 0;
    for (unsigned i = s; i <= n; ++i)
        k = std::max(k, dp[i]);

    std::cout << k << '\n';

    return 0;
}
