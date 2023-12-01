#include <iostream>
#include <string>
#include <vector>

constexpr unsigned M = 1000000007, oo = ~0u >> 1;

struct State {
    unsigned k = oo;
    unsigned q = 0;

    void update(const State& s)
    {
        if (s.k + 1 == k) {
            q += s.q;
            q %= M;
        }

        if (s.k + 1 < k) {
            k = s.k + 1;
            q = s.q;
        }
    }
};

unsigned solve(const std::string& s, const std::string& t)
{
    const size_t n = s.length(), m = t.length();

    std::vector<std::vector<State>> dp(1 + n, std::vector<State>(1 + m));
    for (size_t i = 0; i <= n; ++i) {
        dp[i][0].k = i;
        dp[i][0].q = 1;
    }
    for (size_t j = 0; j <= m; ++j) {
        dp[0][j].k = j;
        dp[0][j].q = 1;
    }
    for (size_t i = 1; i <= n; ++i) {
        for (size_t j = 1; j <= m; ++j) {
            if (s[i-1] == t[j-1]) {
                dp[i][j].update(dp[i-1][j-1]);
            } else {
                dp[i][j].update(dp[i-1][j]);
                dp[i][j].update(dp[i][j-1]);
            }
        }
    }
    return dp[n][m].q;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::string s, t;
    std::cin >> s >> t;

    std::cout << solve(s, t) << '\n';

    return 0;
}
