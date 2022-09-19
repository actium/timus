#include <iostream>
#include <vector>

int main()
{
    size_t n, m;
    std::cin >> n >> m;

    std::vector<std::vector<std::pair<size_t, int>>> g(n);
    for (size_t i = 0; i < m; ++i) {
        unsigned x, y;
        std::cin >> x >> y;

        g[x-1].emplace_back(y-1, 1);
        g[y-1].emplace_back(x-1, -1);
    }

    unsigned s, t;
    std::cin >> s >> t;

    std::vector<unsigned> v(n);
    std::vector<std::pair<size_t, int>> q;

    const auto enqueue = [&](size_t x, unsigned d, int t) {
        if (v[x] == 0 || d < v[x]) {
            q.emplace_back(x, t);
            v[x] = d;
        }
    };

    enqueue(s-1, 1, 0);

    for (size_t i = 0; i < q.size(); ++i) {
        const std::pair<size_t, int> x = q[i];

        for (const std::pair<size_t, int>& y : g[x.first])
            enqueue(y.first, v[x.first] + (y.second != x.second), y.second);
    }

    std::cout << v[t-1] - 2 << '\n';

    return 0;
}
