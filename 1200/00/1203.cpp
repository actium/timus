#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    using interval_t = std::pair<unsigned, unsigned>;

    size_t n;
    std::cin >> n;

    std::vector<interval_t> s(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> s[i].first >> s[i].second;

    std::sort(s.begin(), s.end(), [](const interval_t& x, const interval_t& y) {
        if (x.second != y.second)
            return x.second < y.second;

        return x.first < y.first;
    });

    std::vector<unsigned> dp(1+30000+1);
    for (size_t i = 0, j = 1; j <= 30001; ++j) {
        dp[j] = dp[j-1];
        while (i < n && s[i].second + 1 == j) {
            dp[j] = std::max(dp[j], dp[s[i].first] + 1);
            ++i;
        }
    }

    std::cout << *std::max_element(dp.cbegin(), dp.cend()) << '\n';

    return 0;
}
