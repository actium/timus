#include <iostream>
#include <vector>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned l[3];
    std::cin >> l[0] >> l[1] >> l[2];

    unsigned c[3];
    std::cin >> c[0] >> c[1] >> c[2];

    size_t n;
    std::cin >> n;

    unsigned s, t;
    std::cin >> s >> t;

    std::vector<unsigned> p(n);
    for (size_t i = 1; i < n; ++i)
        std::cin >> p[i];

    if (s > t)
        std::swap(s, t);

    std::vector<unsigned> dp(n, ~0u);
    dp[s-1] = 0;

    size_t x[3] = { s, s, s };
    for (size_t i = s - 1; i < t; ++i) {
        for (size_t k = 0; k < 3; ++k) {
            for (size_t& j = x[k]; j < t && p[j] - p[i] <= l[k]; ++j)
                dp[j] = std::min(dp[j], dp[i] + c[k]);
        }
    }

    std::cout << dp[t-1] << '\n';

    return 0;
}
