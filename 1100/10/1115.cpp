#include <algorithm>
#include <iostream>
#include <vector>

bool search(std::vector<std::pair<unsigned, unsigned>>& f, unsigned w, std::vector<unsigned>& d)
{
    const size_t n = f.size();

    std::vector<std::vector<size_t>> dp(1 + w);
    dp[0].push_back(0);
    for (size_t i = 0; i < n; ++i) {
        for (unsigned k = 0; k < f[i].second; ++k) {
            for (unsigned j = w; j >= f[i].first; --j) {
                if (dp[j - f[i].first].empty())
                    continue;

                if (dp[j].empty() || dp[j].back() != i)
                    dp[j].push_back(i);
            }
        }
    }

    while (w != 0 && !dp[w].empty()) {
        const size_t x = dp[w].back();
        if (f[x].second != 0) {
            d.push_back(f[x].first);
            --f[x].second;
            w -= f[x].first;
        } else {
            dp[w].pop_back();
        }
    }
    return w == 0;
}

bool check(std::vector<std::pair<unsigned, unsigned>> f, const std::vector<unsigned>& t, const std::vector<size_t>& p,
           std::vector<std::vector<unsigned>>& d)
{
    for (const size_t i : p) {
        if (!search(f, t[i], d[i]))
            return false;
    }
    return true;
}

std::vector<std::vector<unsigned>> solve(std::vector<unsigned>& s, const std::vector<unsigned>& t)
{
    const size_t n = s.size(), m = t.size();

    std::sort(s.begin(), s.end());

    std::vector<std::pair<unsigned, unsigned>> f;
    f.emplace_back(s[0], 0);
    for (size_t i = 0; i < n; ++i) {
        if (s[i] != f.back().first)
            f.emplace_back(s[i], 0);

        ++f.back().second;
    }

    std::vector<size_t> p(m);
    for (size_t i = 0; i < m; ++i)
        p[i] = i;

    std::vector<std::vector<unsigned>> d(m);
    while (!check(f, t, p, d)) {
        d.assign(m, {});
        std::next_permutation(p.begin(), p.end());
    }
    return d;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m;
    std::cin >> n >> m;

    std::vector<unsigned> s(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> s[i];

    std::vector<unsigned> t(m);
    for (size_t i = 0; i < m; ++i)
        std::cin >> t[i];

    const std::vector<std::vector<unsigned>> d = solve(s, t);

    for (size_t i = 0; i < m; ++i) {
        std::cout << d[i].size() << '\n';

        for (const unsigned x : d[i])
            std::cout << x << ' ';

        std::cout << '\n';
    }

    return 0;
}
