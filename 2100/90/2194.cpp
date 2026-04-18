#include <iostream>
#include <queue>
#include <vector>

struct State {
    size_t x;
    unsigned d;
};

bool operator <(const State& lhs, const State& rhs)
{
    return lhs.d > rhs.d;
}

int solve(std::vector<unsigned>& p)
{
    const size_t n = p.size();

    for (size_t i = 1; i < n; ++i) {
        if (p[i] != 0)
            p[i] += p[i - p[i]];
    }

    std::vector<unsigned> d[2];
    for (size_t i = 0; i < 2; ++i)
        d[i].resize(n, ~0u);

    std::priority_queue<State> q;

    const auto enqueue = [&](size_t x, unsigned w, bool t) {
        if (w < d[t][x]) {
            d[t][x] = w;
            q.push({ x, w });
        }
    };

    enqueue(0, 0, true);

    while (!q.empty()) {
        const State s = q.top();
        q.pop();

        if (s.d != d[0][s.x] && s.d != d[1][s.x])
            continue;

        for (unsigned k = 1; k <= 6; ++k) {
            size_t y = std::min(s.x + k, n-1);
            y -= p[y];

            enqueue(y, s.d + 1, true);
            if (k == 6)
                enqueue(y, s.d, false);
        }
    }

    return d[1][n-1];
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<unsigned> p(n);
    for (size_t i = 1; i < n-1; ++i)
        std::cin >> p[i];

    std::cout << solve(p) << '\n';

    return 0;
}
