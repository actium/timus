#include <iostream>
#include <vector>

void explore(std::vector<std::vector<size_t>>& g, size_t v, std::vector<unsigned>& r)
{
    r.push_back(v + 1);

    std::vector<size_t> q;
    while (!g[v].empty()) {
        const size_t w = g[v].back();
        g[v].pop_back();
        v = w;
        q.push_back(v);
    }
    for (const size_t x : q) {
        explore(g, x, r);
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<std::vector<size_t>> g(1000);

    unsigned x;
    for (size_t i = 0; i < n; ++i) {
        size_t m;
        std::cin >> m >> x;

        for (size_t j = 1; j <= m; ++j) {
            unsigned v;
            std::cin >> v;

            g[x-1].push_back(v-1);
            x = v;
        }
    }

    std::vector<unsigned> r;
    explore(g, x - 1, r);

    std::cout << r.size() - 1;
    for (const unsigned x : r)
        std::cout << ' ' << x;

    return 0;
}
