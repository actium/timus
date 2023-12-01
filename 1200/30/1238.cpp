#include <iostream>
#include <string>
#include <vector>

struct Folding {
    unsigned k;
    std::string_view p;
    std::string t;
};

std::string fold(unsigned k, std::string_view p)
{
    std::string u = std::to_string(k);
    u.push_back('(');
    u.append(p);
    u.push_back(')');
    if (u.length() <= k * p.length())
        return u;

    std::string v;
    for (unsigned i = 0; i < k; ++i)
        v.append(p);

    return v;
}

std::string solve(const std::string& s)
{
    const size_t n = s.length();

    std::vector<std::vector<Folding>> dp(n, std::vector<Folding>(n));
    for (size_t l = n; l-- > 0; ) {
        dp[l][l].k = 1;
        dp[l][l].p = std::string_view(s.data() + l, 1);
        dp[l][l].t = dp[l][l].p;

        for (size_t r = l + 1; r < n; ++r) {
            for (size_t m = l + 1; m <= r; ++m) {
                if (dp[l][m-1].p == dp[m][r].p) {
                    const unsigned k = dp[l][m-1].k + dp[m][r].k;
                    const std::string t = fold(k, dp[m][r].p);
                    if (dp[l][r].t.empty() || t.length() <= dp[l][r].t.length()) {
                        dp[l][r].k = k;
                        dp[l][r].p = dp[m][r].p;
                        dp[l][r].t = t;
                    }
                }
                if (dp[l][r].t.empty() || dp[l][m-1].t.length() + dp[m][r].t.length() < dp[l][r].t.length()) {
                    dp[l][r].k = 1;
                    dp[l][r].t = dp[l][m-1].t + dp[m][r].t;
                    dp[l][r].p = dp[l][r].t;
                }
            }
        }
    }
    return dp[0][n-1].t;
}

int main()
{
    std::string s;
    std::cin >> s;

    std::cout << solve(s) << '\n';

    return 0;
}
