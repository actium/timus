#include <iostream>
#include <string>
#include <vector>

void print(const std::string& s, const std::vector<size_t>& p, size_t x)
{
    if (x != 0)
        print(s, p, p[x]);

    if (p[x] != 0)
        std::cout << ' ';

    std::cout << s.substr(p[x], x - p[x]);
}

int main()
{
    std::string s;
    std::cin >> s;

    const size_t n = s.length();

    std::vector<std::vector<bool>> v(n, std::vector<bool>(n));
    for (size_t i = 0; i < n; ++i) {
        for (int lb = i, ub = i+0; lb >= 0 && ub < n && s[lb] == s[ub]; v[lb--][ub++] = true);
        for (int lb = i, ub = i+1; lb >= 0 && ub < n && s[lb] == s[ub]; v[lb--][ub++] = true);
    }

    std::vector<unsigned> dp(1 + n);
    for (size_t i = 0; i <= n; ++i)
        dp[i] = i;

    std::vector<size_t> p(1 + n);
    for (size_t i = 1; i <= n; ++i)
        p[i] = i-1;

    for (size_t i = 1; i <= n; ++i) {
        for (size_t j = 0; j < i; ++j) {
            if (v[j][i-1] && dp[j] + 1 < dp[i]) {
                dp[i] = dp[j] + 1;
                p[i] = j;
            }
        }
    }

    std::cout << dp.back() << '\n';

    print(s, p, n);

    return 0;
}
