#include <iostream>
#include <string>
#include <vector>

using state_t = std::pair<unsigned, unsigned>;

constexpr state_t oo = { ~0u, ~0u };

void solve(const std::string_view& s, size_t k, std::vector<std::vector<state_t>>& memo)
{
    const size_t n = s.length();
    if (n < 10)
        memo[n][k] = { 0, 0 };

    if (memo[n][k] == oo) {
        int x = 9;
        while (x >= 0 && s[x] != '0')
            --x;

        solve(s.substr(10), k, memo);
        memo[n][k] = state_t(memo[n-10][k].first + (x != 9), 0);

        if (x != -1 && 9 - x <= k) {
            const size_t d = 9 - x;
            solve(s.substr(10 - d), k - d, memo);
            if (memo[n+d-10][k-d].first < memo[n][k].first) {
                memo[n][k].first = memo[n+d-10][k-d].first;
                memo[n][k].second = d;
            }
        }
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, k;
    std::cin >> n >> k;

    std::string s;
    std::cin >> s;

    std::vector<std::vector<state_t>> memo(1 + n, std::vector<state_t>(1 + k, oo));
    solve(s, k, memo);

    std::cout << memo[n][k].first << '\n';

    std::vector<size_t> p;
    for (size_t i = 0, d = 0; i < n + d; i += 10) {
        const size_t q = memo[n+d-i][k].second;
        for (size_t j = 0; j < memo[n+d-i][k].second; ++j)
            p.push_back(i + j);

        d += q;
        k -= q;
    }

    std::cout << p.size();
    for (const size_t x : p)
        std::cout << ' ' << 1 + x;

    return 0;
}
