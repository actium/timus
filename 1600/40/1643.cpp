#include <iostream>
#include <queue>
#include <string>
#include <vector>

using spot_t = std::pair<size_t, size_t>;

constexpr unsigned oo = ~0u;

void search(const std::vector<std::string>& g, const std::vector<std::vector<spot_t>>& p,
            const spot_t& s, const spot_t& t,
            std::vector<std::vector<unsigned>>& d)
{
    const size_t n = g.size(), m = g[0].size();

    std::queue<spot_t> q;

    const auto enqueue = [&](size_t r, size_t c, unsigned v) {
        if (r >= n || c >= m || g[r][c] == '#')
            return;

        if (r == t.first && c == t.second)
            return;

        if (g[r][c] >= 'A' && g[r][c] <= 'Z' && v < d[r][c]) {
            for (const spot_t& t : p[g[r][c] - 'A']) {
                d[t.first][t.second] = v;
                q.emplace(t.first, t.second);
            }
        }

        if (v < d[r][c]) {
            d[r][c] = v;
            q.emplace(r, c);
        }
    };

    enqueue(s.first, s.second, 0);
    while (!q.empty()) {
        const auto [r, c] = q.front();
        q.pop();

        enqueue(r - 1, c + 0, d[r][c] + 1);
        enqueue(r - 1, c + 1, d[r][c] + 1);
        enqueue(r + 0, c + 1, d[r][c] + 1);
        enqueue(r + 1, c + 1, d[r][c] + 1);
        enqueue(r + 1, c + 0, d[r][c] + 1);
        enqueue(r + 1, c - 1, d[r][c] + 1);
        enqueue(r + 0, c - 1, d[r][c] + 1);
        enqueue(r - 1, c - 1, d[r][c] + 1);
    }
}

unsigned solve(const std::vector<std::string>& g)
{
    const size_t n = g.size(), m = g[0].size();

    spot_t s[2], t;
    std::vector<std::vector<spot_t>> p(26);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            switch (g[i][j]) {
                case '.':
                    break;

                case '#':
                    break;

                case '$':
                    s[0].first = i;
                    s[0].second = j;
                    break;

                case '!':
                    s[1].first = i;
                    s[1].second = j;
                    break;

                case '*':
                    t.first = i;
                    t.second = j;
                    break;

                default:
                    p[g[i][j] - 'A'].emplace_back(i, j);
                    break;
            }
        }
    }

    std::vector<std::vector<unsigned>> d[2];
    for (size_t i = 0; i < 2; ++i) {
        d[i].resize(n, std::vector<unsigned>(m, oo));
        search(g, p, s[i], t, d[i]);
    }

    unsigned v = oo;

    const auto optimize = [&](size_t r, size_t c) {
        if (r < n && c < m && g[r][c] != '#')
            v = std::min(v, std::max(d[0][r][c], d[1][r][c]));
    };

    optimize(t.first - 1, t.second + 0);
    optimize(t.first - 1, t.second + 1);
    optimize(t.first + 0, t.second + 1);
    optimize(t.first + 1, t.second + 1);
    optimize(t.first + 1, t.second + 0);
    optimize(t.first + 1, t.second - 1);
    optimize(t.first + 0, t.second - 1);
    optimize(t.first - 1, t.second - 1);

    return v;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m;
    std::cin >> n >> m;

    std::vector<std::string> g(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> g[i];

    const unsigned q = solve(g);

    if (q != oo)
        std::cout << q + 1 << '\n';
    else
        std::cout << "Impossible" << '\n';

    return 0;
}
