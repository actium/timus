#include <iostream>
#include <queue>
#include <vector>

using grid_t = std::vector<std::vector<unsigned>>;
using spot_t = std::pair<unsigned, unsigned>;

constexpr unsigned oo = ~0u;

void fill(const grid_t& h, const spot_t& s, grid_t& t)
{
    const size_t n = h.size(), m = h[0].size();

    std::queue<spot_t> q;

    const auto enqueue = [&](unsigned i, unsigned j, unsigned v) {
        if (t[i-1][j-1] == oo) {
            t[i-1][j-1] = v;
            q.emplace(i, j);
        }
    };

    enqueue(s.first, s.second, 0);
    while (!q.empty()) {
        const spot_t x = q.front();
        q.pop();

        const unsigned i = x.first, j = x.second;
        if (i > 1 && h[i-1][j-1] >= h[i-2][j-1])
            enqueue(i - 1, j, t[i-1][j-1] + 1);
        if (i < n && h[i-1][j-1] >= h[i][j-1])
            enqueue(i + 1, j, t[i-1][j-1] + 1);
        if (j > 1 && h[i-1][j-1] >= h[i-1][j-2])
            enqueue(i, j - 1, t[i-1][j-1] + 1);
        if (j < m && h[i-1][j-1] >= h[i-1][j])
            enqueue(i, j + 1, t[i-1][j-1] + 1);
    }
}

int escape(const grid_t& h, const grid_t& t, const spot_t& s)
{
    const size_t n = h.size(), m = h[0].size();

    grid_t u(n, std::vector<unsigned>(m, oo));

    std::queue<std::pair<spot_t, unsigned>> q;

    const auto enqueue = [&](unsigned i, unsigned j, unsigned e, unsigned v) {
        if (e < t[i-1][j-1] && v < u[i-1][j-1]) {
            u[i-1][j-1] = v;
            q.emplace(std::make_pair(i, j), e);
        }
    };

    enqueue(s.first, s.second, 0, 0);
    while (!q.empty()) {
        const auto x = q.front();
        q.pop();

        const unsigned i = x.first.first, j = x.first.second, e = x.second;
        if (i > 1) {
            const int d = h[i-2][j-1] - h[i-1][j-1];
            enqueue(i - 1, j, e + 1, std::max<int>(u[i-1][j-1], d));
        }
        if (i < n) {
            const int d = h[i][j-1] - h[i-1][j-1];
            enqueue(i + 1, j, e + 1, std::max<int>(u[i-1][j-1], d));
        }
        if (j > 1) {
            const int d = h[i-1][j-2] - h[i-1][j-1];
            enqueue(i, j - 1, e + 1, std::max<int>(u[i-1][j-1], d));
        }
        if (j < m) {
            const int d = h[i-1][j] - h[i-1][j-1];
            enqueue(i, j + 1, e + 1, std::max<int>(u[i-1][j-1], d));
        }
    }

    unsigned v = oo;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            if (t[i][j] == oo)
                v = std::min(v, u[i][j]);
        }
    }
    return v;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m;
    std::cin >> n >> m;

    grid_t h(n, std::vector<unsigned>(m));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j)
            std::cin >> h[i][j];
    }

    spot_t r;
    std::cin >> r.first >> r.second;

    spot_t w;
    std::cin >> w.first >> w.second;

    grid_t t(n, std::vector<unsigned>(m, oo));
    fill(h, w, t);

    std::cout << escape(h, t, r) << '\n';

    return 0;
}
