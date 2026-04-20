#include <algorithm>
#include <iostream>
#include <vector>

std::pair<int, int> balance(const std::string& s)
{
    std::pair<int, int> b = { 0, 0 };
    for (const char c : s) {
        b.first += (c == '(' ? 1 : -1);
        b.second = std::min(b.second, b.first);
    }
    return b;
}

void solve(const std::vector<std::string>& s)
{
    const size_t n = s.size();

    std::vector<std::pair<int, int>> b(n);
    for (size_t i = 0; i < n; ++i)
        b[i] = balance(s[i]);

    std::vector<size_t> p(n);
    for (size_t i = 0; i < n; ++i)
        p[i] = i;

    std::sort(p.begin(), p.end(), [&](size_t i, size_t j) {
        if (b[i].first < 0)
            return b[j].first < 0 && b[i].first - b[i].second > b[j].first - b[j].second;

        return b[j].first < 0 || b[i].second > b[j].second;
    });

    std::vector<std::pair<size_t, size_t>> sources;
    sources.emplace_back(n, 0);

    std::vector<size_t> dp(5001), t(5001);
    for (const size_t i : p) {
        std::vector<size_t> ndp = dp, nt = t;
        for (int x = 5000, d = b[i].first; x >= -b[i].second; --x) {
            if (x + d < 0 || x + d > 5000)
                continue;

            if (x != 0 && dp[x] == 0)
                continue;

            if (ndp[x+d] < dp[x] + s[i].length()) {
                ndp[x+d] = dp[x] + s[i].length();
                sources.emplace_back(i, t[x]);
                nt[x+d] = sources.size() - 1;
            }
        }
        std::swap(dp, ndp);
        std::swap(t, nt);
    }

    std::vector<size_t> path;
    if (dp[0] != 0) {
        for (size_t x = t[0]; sources[x].first != n; x = sources[x].second)
            path.push_back(sources[x].first);
    }

    std::cout << dp[0] << ' ' << path.size() << '\n';
    for (auto it = path.rbegin(); it != path.rend(); ++it)
        std::cout << 1 + *it << ' ';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<std::string> s(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> s[i];

    solve(s);

    return 0;
}
