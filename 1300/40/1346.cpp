#include <iostream>
#include <vector>

unsigned solve(const std::vector<int>& s)
{
    const size_t n = s.size();

    std::vector<unsigned> dp1(n), dp2(n);
    dp1[0] = dp2[0] = 1;
    for (size_t i = 1; i < n; ++i) {
        dp1[i] = std::min(dp1[i-1] + (s[i] < s[i-1]), dp2[i-1] + 1);
        dp2[i] = std::min(dp1[i-1] + 1, dp2[i-1] + (s[i] > s[i-1]));
    }

    return std::min(dp1[n-1], dp2[n-1]);
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned a, b;
    std::cin >> a >> b;

    unsigned n = b - a + 1;
    std::vector<int> s(n);

    for (unsigned i = 0; i < n; ++i)
        std::cin >> s[i];

    std::cout << solve(s) << '\n';

    return 0;
}
