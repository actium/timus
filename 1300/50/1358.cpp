#include <iostream>
#include <vector>

using graph_t = std::vector<std::vector<size_t>>;

struct Point {
    int x;
    int y;
};

void place(const graph_t& g, size_t u, size_t v, int dx, int dy, std::vector<Point>& p)
{
    for (const size_t i : g[u]) {
        if (i != v) {
            place(g, i, u, dx, dy - 2, p);
            dx = p[i].x + 2;
        }
    }

    p[u].x = dx;
    p[u].y = dy;
}

void solve(graph_t& g)
{
    const size_t n = g.size();

    std::vector<Point> p(n);
    place(g, 0, 0, -1000, 1000, p);

    for (size_t i = 0; i < n; ++i)
        std::cout << p[i].x << ' ' << p[i].y << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    graph_t g(n);
    for (size_t i = 1; i < n; ++i) {
        unsigned u, v;
        std::cin >> u >> v;

        g[u-1].push_back(v-1);
        g[v-1].push_back(u-1);
    }

    solve(g);

    return 0;
}
