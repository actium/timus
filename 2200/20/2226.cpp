#include <algorithm>
#include <iostream>
#include <vector>

struct Edge {
    size_t v;
    unsigned w;
    unsigned x;
};

using graph_t = std::vector<std::vector<Edge>>;

unsigned explore(graph_t& graph, size_t u, size_t p)
{
    Edge* edge = nullptr;
    for (auto& e : graph[u]) {
        if (e.v != p && (edge == nullptr || e.w < edge->w))
            edge = &e;
    }

    if (edge == nullptr)
        return static_cast<unsigned>(u) + 1;

    if (edge->x == 0)
        edge->x = explore(graph, edge->v, u);

    return edge->x;
}

void solve(graph_t& graph)
{
    const size_t n = graph.size();

    for (size_t i = 0; i < n; ++i) {
        if (graph[i].size() < 3)
            continue;

        std::sort(graph[i].begin(), graph[i].end(), [](const Edge& lhs, const Edge& rhs) {
            return lhs.w < rhs.w;
        });
        graph[i].resize(2);
    }

    for (size_t i = 0; i < n; ++i)
        std::cout << explore(graph, i, n) << " \n"[i+1==n];
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    graph_t graph(n);
    for (size_t i = 1; i < n; ++i) {
        unsigned u, v, w;
        std::cin >> u >> v >> w;

        graph[u-1].push_back({ v-1, w, 0 });
        graph[v-1].push_back({ u-1, w, 0 });
    }

    solve(graph);

    return 0;
}
