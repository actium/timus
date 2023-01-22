#include <algorithm>
#include <iostream>
#include <string>

unsigned C(unsigned n, unsigned k)
{
    unsigned dp[1+n][1+k];
    for (unsigned i = 0; i <= n; ++i) {
        dp[i][0] = 1;

        for (unsigned j = 1, b = std::min(i, k + 1); j < b; ++j)
            dp[i][j] = dp[i-1][j-1] + dp[i-1][j];

        if (i <= k)
            dp[i][i] = 1;
    }
    return dp[n][k];
}

int main()
{
    std::string s;
    std::cin >> s;

    unsigned k;
    std::cin >> k;

    k = std::min(k, 26u);

    unsigned f[26] = {};
    for (const char c : s)
        ++f[c - 'a'];

    std::sort(std::begin(f), std::end(f), std::greater<unsigned>());

    unsigned q = 0;
    for (unsigned i = 0; i < k; ++i)
        q += f[i];

    unsigned l = 1;
    for (unsigned i = k - 1; i > 0 && f[i] != 0 && f[i-1] == f[i]; --i)
        ++l;

    unsigned r = 0;
    for (unsigned i = k; i < 26 && f[i] != 0 && f[i] == f[i-1]; ++i)
        ++r;

    std::cout << q << ' ' << C(l + r, l) << '\n';

    return 0;
}
