#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::string s;
    std::cin >> s;

    const size_t n = s.length();
    if (n == 0)
        return 0;

    std::vector<std::vector<unsigned>> dp(1+n, std::vector<unsigned>(n));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i; j < n; ++j)
            dp[i][j] = ~0u;
    }

    std::vector<std::vector<std::string>> t(1+n, std::vector<std::string>(n));
    for (size_t i = n; i-- > 0; ) {
        dp[i][i] = 1;
        t[i][i] = (s[i] == '(' || s[i] == ')' ? "()" : "[]");

        for (size_t j = i+1; j < n; ++j) {
            if (s[i] == '(' && s[j] == ')' && dp[i+1][j-1] < dp[i][j]) {
                dp[i][j] = dp[i+1][j-1];
                t[i][j] = '(' + t[i+1][j-1] + ')';
            }
            if (s[i] == '[' && s[j] == ']' && dp[i+1][j-1] < dp[i][j]) {
                dp[i][j] = dp[i+1][j-1];
                t[i][j] = '[' + t[i+1][j-1] + ']';
            }

            for (size_t k = i; k < j; ++k) {
                if (dp[i][j] > dp[i][k] + dp[k+1][j]) {
                    dp[i][j] = dp[i][k] + dp[k+1][j];
                    t[i][j] = t[i][k] + t[k+1][j];
                }
            }
        }
    }

    std::cout << t[0][n-1] << '\n';

    return 0;
}
