#include <iostream>
#include <numeric>
#include <queue>
#include <vector>

std::vector<unsigned> compute_distances(unsigned n, unsigned m, unsigned x)
{
    std::vector<unsigned> d(n, ~0u);
    {
        std::queue<std::pair<unsigned, unsigned>> q;
        std::vector<bool> v(n);

        const auto enqueue = [&](unsigned x, unsigned k) {
            if (!v[x]) {
                q.emplace(x, k);
                d[x] = k;
                v[x] = true;
            }
        };

        enqueue(x, 0);
        while (!q.empty()) {
            const std::pair<unsigned, unsigned> p = q.front();
            q.pop();

            if (p.first >= m)
                enqueue(p.first - m, p.second + 1);

            if (p.first + m < n)
                enqueue(p.first + m, p.second + 1);

            enqueue((p.first + n - 1) % n, p.second + 1);
            enqueue((p.first + 1) % n, p.second + 1);
        }
    }
    return d;
}

void solve(unsigned n, unsigned m)
{
    std::vector<unsigned> d = compute_distances(n, m, 0);
    unsigned v = std::accumulate(d.begin(), d.end(), 0);
    for (unsigned i = 1; i < n; ++i) {
        std::vector<unsigned> c = compute_distances(n, m, i);

        const unsigned u = std::accumulate(c.begin(), c.end(), 0);
        if (u < v) {
            d.swap(c);
            v = u;
        }
    }

    std::cout << "Mean = " << std::fixed << double(v) / n << '\n';
    for (unsigned i = 0; i < n; ++i)
        std::cout << d[i] << " \n"[(i + 1) % m == 0];
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, m;
    std::cin >> n >> m;

    solve(n, m);

    return 0;
}
