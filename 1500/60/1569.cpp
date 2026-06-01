#include <iostream>
#include <queue>
#include <vector>

using graph_t = std::vector<std::vector<std::pair<unsigned, unsigned>>>;

constexpr unsigned oo = ~0u >> 1;

struct Node {
    unsigned u;
    unsigned w;
};

bool operator <(const Node& lhs, const Node& rhs)
{
    return lhs.w > rhs.w;
}

std::vector<unsigned> mdst(const graph_t& graph)
{
    const size_t n = graph.size();

    std::vector<unsigned> distances(n, oo), parents(n, oo);
    std::priority_queue<Node> queue;

    const auto enqueue = [&](unsigned u, unsigned d, unsigned p) {
        if (d < distances[u]) {
            distances[u] = d;
            parents[u] = p;
            queue.push({ d, u });
        }
    };

    enqueue(0, 0, oo);
    while (!queue.empty()) {
        const auto [d, u] = queue.top();
        queue.pop();

        if (d != distances[u])
            continue;

        for (const auto& [v, w] : graph[u])
            enqueue(v, d + w, u);
    }

    return parents;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m;
    std::cin >> n >> m;

    std::vector<std::pair<unsigned, unsigned>> edges(m);
    for (size_t i = 0; i < m; ++i)
        std::cin >> edges[i].first >> edges[i].second;

    std::vector<std::vector<unsigned>> distances(1+n, std::vector<unsigned>(1+n, oo));
    for (size_t v = 1; v <= n; ++v)
        distances[v][v] = 0;

    for (const auto& [u, v] : edges) {
        distances[u][v] = 2;
        distances[v][u] = 2;
    }

    for (size_t k = 1; k <= n; ++k) {
        for (size_t i = 1; i <= n; ++i) {
            for (size_t j = 1; j <= n; ++j)
                distances[i][j] = std::min(distances[i][j], distances[i][k] + distances[k][j]);
        }
    }

    unsigned best_u = 0, best_v = 0, best_radius = oo;
    for (unsigned u = 1; u <= n; ++u) {
        unsigned r = 0;
        for (unsigned v = 1; v <= n; ++v)
            r = std::max(r, distances[u][v]);

        if (r < best_radius) {
            best_u = u;
            best_v = u;
            best_radius = r;
        }
    }
    for (const auto& [u, v] : edges) {
        unsigned r = 0;
        for (unsigned w = 1; w <= n; ++w)
            r = std::max(r, std::min(distances[u][w], distances[v][w]) + 1);

        if (r < best_radius) {
            best_u = u;
            best_v = v;
            best_radius = r;
        }
    }

    graph_t graph(1+n);
    for (const auto& [u, v] : edges) {
        graph[u].emplace_back(v, 2);
        graph[v].emplace_back(u, 2);
    }
    graph[0].emplace_back(best_u, distances[best_u][best_v] / 2);
    graph[0].emplace_back(best_v, distances[best_u][best_v] / 2);

    const std::vector<unsigned> parents = mdst(graph);
    for (unsigned u = 1; u <= n; ++u) {
        if (parents[u] != oo && parents[u] != 0)
            std::cout << u << ' ' << parents[u] << '\n';
    }

    if (best_u != best_v)
        std::cout << best_u << ' ' << best_v << '\n';

    return 0;
}
