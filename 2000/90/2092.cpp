#include <algorithm>
#include <iostream>
#include <vector>

double solve(std::vector<std::pair<unsigned, unsigned>>& sd, const std::vector<std::pair<unsigned, unsigned>>& kp)
{
    using integer = unsigned long long;

    const size_t n = sd.size();

    std::vector<unsigned> r(101, ~0u);
    for (const std::pair<unsigned, unsigned>& x : kp)
        r[x.second] = std::min(r[x.second], x.first);

    integer u = 0, v = 0;
    for (const std::pair<unsigned, unsigned>& x : sd) {
        u += x.first;
        v += x.first * (100 - x.second);
    }

    for (unsigned p = 100, k = n + 1; p > 0; --p) {
        if (r[p] >= k)
            continue;

        k = r[p];

        std::sort(sd.begin(), sd.end(), [p](const std::pair<unsigned, unsigned>& lhs, const std::pair<unsigned, unsigned>& rhs) {
            return lhs.first * p + rhs.first * rhs.second > rhs.first * p + lhs.first * lhs.second;
        });

        std::vector<integer> ss(1 + n);
        for (size_t i = 0; i < n; ++i)
            ss[n-i-1] = ss[n-i] + sd[n-i-1].first * sd[n-i-1].second;

        integer ps = 0;
        for (unsigned j = 0; j < k; ++j)
            ps += sd[j].first;

        for (unsigned j = k; j <= n; ++j) {
            v = std::min(v, ps * (100 - p) + (u - ps) * 100 - ss[j]);
            ps += sd[j].first;
        }
    }

    return v / 100.0;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m;
    std::cin >> n >> m;

    std::vector<std::pair<unsigned, unsigned>> sd(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> sd[i].first >> sd[i].second;

    std::vector<std::pair<unsigned, unsigned>> kp(m);
    for (size_t i = 0; i < m; ++i)
        std::cin >> kp[i].first >> kp[i].second;

    std::cout << std::fixed << solve(sd, kp) << '\n';

    return 0;
}
