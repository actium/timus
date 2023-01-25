#include <iostream>
#include <vector>

using graph_t = std::vector<std::vector<size_t>>;

void traverse(const graph_t& g, size_t u, std::vector<bool>& v)
{
    v[u] = true;

    for (const size_t x : g[u]) {
        if (!v[x])
            traverse(g, x, v);
    }
}

int main()
{
    size_t n;
    std::cin >> n;

    std::string names[200];
    int q[200][3];
    for (size_t i = 0; i < n; ++i)
        std::cin >> names[i] >> q[i][0] >> q[i][1] >> q[i][2];

    graph_t g(n);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            const bool p1 = (q[i][0] > q[j][0]), p2 = (q[i][1] > q[j][1]), p3 = (q[i][2] > q[j][2]);
            if (p1 && p2 || p1 && p3 || p2 && p3)
                g[i].push_back(j);
        }
    }

    const std::vector<bool> w(n, true);
    for (size_t i = 0; i < n; ++i) {
        std::vector<bool> v(n);
        traverse(g, i, v);
        if (v == w)
            std::cout << names[i] << '\n';
    }

    return 0;
}
