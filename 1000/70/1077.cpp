#include <iostream>
#include <vector>

using graph_t = std::vector<std::vector<size_t>>;
using path_t = std::vector<size_t>;

void traverse(const graph_t& g, size_t u, size_t p, std::vector<unsigned>& c, path_t& path, std::vector<path_t>& paths)
{
    c[u] = 1;

    path.push_back(u);
    for (const size_t v : g[u]) {
        if (v == p)
            continue;

        if (c[v] == 0)
            traverse(g, v, u, c, path, paths);

        if (c[v] == 1) {
            auto it = path.rbegin();
            while (*it != v)
                ++it;

            paths.emplace_back(path.rbegin(), std::next(it));
        }
    }
    path.pop_back();

    c[u] = 2;
}

void solve(const graph_t& g)
{
    const size_t n = g.size();

    std::vector<path_t> paths;

    std::vector<unsigned> c(n);
    for (size_t i = 0; i < n; ++i) {
        if (c[i] == 0) {
            path_t path;
            traverse(g, i, i, c, path, paths);
        }
    }

    std::cout << paths.size() << '\n';
    for (const path_t& path : paths) {
        std::cout << path.size();

        for (const size_t x : path)
            std::cout << ' ' << 1+x;

        std::cout << '\n';
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m;
    std::cin >> n >> m;

    graph_t g(n);
    for (size_t i = 0; i < m; ++i) {
        unsigned u, v;
        std::cin >> u >> v;

        g[u-1].push_back(v-1);
        g[v-1].push_back(u-1);
    }

    solve(g);

    return 0;
}
