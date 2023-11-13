#include <algorithm>
#include <iostream>
#include <vector>

using interval_t = std::pair<unsigned, unsigned>;

void solve(size_t m, const std::vector<interval_t>& s, unsigned p)
{
    const size_t k = s.size();

    std::vector<std::pair<size_t, int>> events(2 * k);
    for (size_t i = 0; i < k; ++i) {
        events[i+0] = { i, +1 };
        events[i+k] = { i, -1 };
    }

    std::sort(events.begin(), events.end(), [&](const auto& lhs, const auto& rhs) {
        const unsigned lt = (lhs.second == -1 ? s[lhs.first].second : s[lhs.first].first);
        const unsigned rt = (rhs.second == -1 ? s[rhs.first].second : s[rhs.first].first);
        return lt != rt ? lt < rt : lhs.second < rhs.second;
    });

    std::vector<size_t> q, v, x(k, m);
    for (const std::pair<size_t, int>& e : events) {
        if (e.second == -1) {
            if (x[e.first] != m) {
                v.push_back(e.first);
                x[q.back()] = x[e.first];
                q[x[e.first]] = q.back();
                q.pop_back();
            }
            continue;
        }

        if (q.size() < m) {
            x[e.first] = q.size();
            q.push_back(e.first);
            continue;
        }

        size_t i = 0;
        for (size_t j = 1; j < m; ++j) {
            if (s[q[j]].second > s[q[i]].second)
                i = j;
        }

        if (s[e.first].second < s[q[i]].second) {
            x[e.first] = i;
            x[q[i]] = m;
            q[i] = e.first;
        }
    }

    std::cout << v.size() * p << '\n';
    for (const size_t i : v)
        std::cout << 1 + i << ' ';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m, k;
    std::cin >> n >> m >> k;

    unsigned p;
    std::cin >> p;

    std::vector<interval_t> s(k);
    for (size_t i = 0; i < k; ++i)
        std::cin >> s[i].first >> s[i].second;

    solve(m, s, p);

    return 0;
}
