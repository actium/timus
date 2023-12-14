#include <iostream>
#include <numeric>
#include <vector>

unsigned hungarian(const std::vector<std::vector<unsigned>> c)
{
    const size_t n = c.size();

    std::vector<int> u(n + 1), v(n + 1), p(n + 1);
    for (size_t i = 1; i <= n; ++i) {
        p[0] = i;

        std::vector<unsigned> dist(n + 1, ~0u);
        std::vector<int> pre(n + 1, -1);
        std::vector<bool> done(n + 1);

        size_t x = 0;
        do {
            done[x] = true;

            unsigned d = ~0u;
            for (size_t s = x, j = 1; j <= n; ++j) {
                if (done[j])
                    continue;

                const unsigned t = c[p[s]-1][j-1] - u[p[s]] - v[j];
                if (t < dist[j]) {
                    dist[j] = t;
                    pre[j] = s;
                }
                if (dist[j] < d) {
                    d = dist[j];
                    x = j;
                }
            }
            for (size_t j = 0; j <= n; ++j) {
                if (done[j]) {
                    u[p[j]] += d;
                    v[j] -= d;
                } else {
                    dist[j] -= d;
                }
            }
        } while (p[x] != 0);

        while (x != 0) {
            const size_t s = pre[x];
            p[x] = p[s];
            x = s;
        }
    }

    return -v[0];
}

unsigned solve(const std::vector<std::vector<unsigned>>& a)
{
    const size_t n = a.size();

    std::vector<std::vector<unsigned>> c(n, std::vector<unsigned>(n));
    for (size_t i = 0; i < n; ++i) {
        const unsigned rs = std::accumulate(a[i].begin(), a[i].end(), 0);
        for (size_t j = 0; j < n; ++j)
            c[i][j] = rs - a[i][j];
    }

    return hungarian(c);
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<std::vector<unsigned>> a(n, std::vector<unsigned>(n));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j)
            std::cin >> a[i][j];
    }

    std::cout << solve(a) << '\n';

    return 0;
}
