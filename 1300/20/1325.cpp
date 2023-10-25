#include <iostream>
#include <queue>
#include <string>
#include <vector>

using position_t = std::pair<unsigned, unsigned>;
using distance_t = std::pair<unsigned, unsigned>;
using state_t = std::pair<unsigned, position_t>;

constexpr unsigned oo = ~0u;

std::pair<unsigned, unsigned> solve(const std::vector<std::string>& b, const position_t& s, const position_t& t)
{
    const size_t n = b.size(), m = b[0].size();

    std::priority_queue<state_t, std::vector<state_t>, std::greater<state_t>> q[2];
    std::vector<std::vector<distance_t>> v(n, std::vector<distance_t>(m, {oo, oo}));
    unsigned k = 0;

    const auto enqueue = [&](size_t r, size_t c, const distance_t& d) {
        if (d.first < v[r][c].first || (d.first == v[r][c].first && d.second < v[r][c].second)) {
            q[d.first > k].emplace(d.second, std::make_pair(r, c));
            v[r][c] = d;
        }
    };

    const auto dequeue = [&] {
        if (q[0].empty()) {
            q[0] = std::move(q[1]);
            ++k;
        }

        const state_t u = q[0].top();
        q[0].pop();
        return u;
    };

    enqueue(s.first - 1, s.second - 1, std::make_pair(0, 1));
    while (q[0].size() + q[1].size() != 0) {
        const state_t u = dequeue();
        if (u.second.first == t.first - 1 && u.second.second == t.second - 1)
            return { u.first, k };

        for (const int dr : { -1, 0, +1 }) {
            for (const int dc : { -1, 0, +1 }) {
                if (dr == 0 && dc == 0)
                    continue;

                if (u.second.first + dr >= n || u.second.second + dc >= m)
                    continue;

                if (b[u.second.first + dr][u.second.second + dc] == '0')
                    continue;

                const size_t a = (b[u.second.first][u.second.second] != b[u.second.first + dr][u.second.second + dc]);
                enqueue(u.second.first + dr, u.second.second + dc, std::make_pair(k + a, u.first + 1));
            }
        }
    }

    return { 0, 0 };
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m;
    std::cin >> n >> m;

    position_t s;
    std::cin >> s.first >> s.second;

    position_t t;
    std::cin >> t.first >> t.second;

    std::vector<std::string> b(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> b[i];

    const std::pair<unsigned, unsigned> v = solve(b, s, t);
    std::cout << v.first << ' ' << v.second << '\n';

    return 0;
}
