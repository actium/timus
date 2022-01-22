#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

constexpr char tt[] = "22233344115566070778889990";

constexpr unsigned oo = ~0u;

void solve(const std::string& pn, const std::vector<std::string>& w)
{
    const size_t n = pn.length();

    std::vector<std::pair<std::string, size_t>> ds;
    for (size_t i = 0; i < w.size(); ++i) {
        std::string t = w[i];
        for (char& c : t)
            c = tt[c-'a'];

        if (pn.find(t) != std::string::npos)
            ds.emplace_back(t, i);
    }

    std::sort(ds.begin(), ds.end(), [](const auto& a, const auto& b) {
        return a.first.length() < b.first.length();
    });

    std::vector<std::pair<unsigned, std::string>> dp(n + 1, { oo, std::string() });
    dp[0].first = 0;
    dp[n].second = "No solution.";
    for (size_t i = 0; i < n; ++i) {
        if (dp[i].first == oo)
            continue;

        for (const auto& s : ds) {
            const size_t m = s.first.length();
            if (pn.compare(i, m, s.first) != 0)
                continue;

            if (dp[i].first + 1 < dp[i+m].first) {
                dp[i+m].first = dp[i].first + 1;
                dp[i+m].second = dp[i].second + ' ' + w[s.second];
            }
        }
    }

    std::cout << dp[n].second << '\n';
}

void test_case(const std::string& pn)
{
    size_t n;
    std::cin >> n;

    std::vector<std::string> w(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> w[i];

    solve(pn, w);
}

int main()
{
    for (std::string s; std::cin >> s && s != "-1"; test_case(s));

    return 0;
}
