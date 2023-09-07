#include <iostream>
#include <vector>

using Graph = std::vector<std::vector<std::pair<unsigned, unsigned>>>;

struct Path {
    std::vector<unsigned> points;
    double probability;
};

Path solve(const Graph& graph, unsigned start, unsigned target)
{
    const size_t n = graph.size();

    std::vector<int> sources(n, -1);
    std::vector<unsigned> distances(n);
    std::vector<double> chances(n);

    std::vector<unsigned> queue;
    bool in_queue[100000] = {};

    const auto enqueue = [&](unsigned node, unsigned source, unsigned distance, double chance) {
        if (sources[node] == -1) {
            sources[node] = source;
            distances[node] = distance;
        }
        if (distance == distances[node] && chance > chances[node]) {
            sources[node] = source;
            chances[node] = chance;
        }
        if (!in_queue[node]) {
            queue.push_back(node);
            in_queue[node] = true;
        }
    };

    enqueue(start, start, 0, 1);
    for (size_t i = 0; i < queue.size(); ++i) {
        const size_t node = queue[i];

        for (const auto [u, c] : graph[node]) {
            if (chances[node] * (100 - c) > chances[u] * 100)
                enqueue(u, node, distances[node] + 1, chances[node] * (100 - c) / 100);
        }
    }

    Path path;
    for (size_t x = target; x != start; x = sources[x])
        path.points.push_back(1 + x);

    path.points.push_back(1 + start);
    path.probability = 1 - chances[target];
    return path;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m;
    std::cin >> n >> m;

    unsigned s, t;
    std::cin >> s >> t;

    Graph graph(n);
    for (size_t i = 0; i < m; ++i) {
        unsigned a, b, p;
        std::cin >> a >> b >> p;

        graph[a-1].emplace_back(b - 1, p);
        graph[b-1].emplace_back(a - 1, p);
    }

    const Path path = solve(graph, s - 1, t - 1);
    std::cout << path.points.size() << ' ' << std::fixed << path.probability << '\n';
    for (auto it = path.points.rbegin(); it != path.points.rend(); ++it)
        std::cout << *it << ' ';

    return 0;
}
