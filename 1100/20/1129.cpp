#include <iostream>
#include <vector>

using graph_t = std::vector<std::vector<unsigned>>;

void paint(const graph_t& g, size_t u, std::vector<size_t>& f, std::vector<std::vector<char>>& c)
{
    const size_t v = f[u], n = f.size();
    if (v != n) {
        f[u] = n;
        f[v] = n;

        paint(g, v, f, c);
    }

    for (const unsigned x : g[u]) {
        if (c[u][x-1] == ' ') {
            c[u][x-1] = 'G';
            c[x-1][u] = 'Y';

            paint(g, x-1, f, c);
        }
    }
}

void solve(const graph_t& g)
{
    const size_t n = g.size();

    std::vector<size_t> f(n, n);
    {
        std::vector<size_t> p;
        for (size_t i = 0; i < n; ++i) {
            if (g[i].size() % 2 == 0)
                continue;

            if (p.empty()) {
                p.push_back(i);
            } else {
                f[i] = p.back();
                f[p.back()] = i;
                p.pop_back();
            }
        }
    }

    std::vector<std::vector<char>> c(n, std::vector<char>(n, ' '));
    for (size_t i = 0; i < n; ++i)
        paint(g, i, f, c);

    for (size_t i = 0; i < n; ++i) {
        for (const unsigned x : g[i])
            std::cout << c[i][x-1] << ' ';

        std::cout << '\n';
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    graph_t g(n);
    for (size_t i = 0; i < n; ++i) {
        size_t k;
        std::cin >> k;

        g[i].resize(k);

        for (size_t j = 0; j < k; ++j)
            std::cin >> g[i][j];
    }

    solve(g);

    return 0;
}
