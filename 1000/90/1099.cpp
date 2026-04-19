#include <iostream>
#include <queue>
#include <vector>

using graph_t = std::vector<std::vector<unsigned>>;

void search(const graph_t& g, std::vector<unsigned>& times, std::vector<size_t>& parents, std::vector<size_t>& mates, size_t root)
{
    const size_t n = g.size();

    std::vector<unsigned> labels(n);

    std::vector<size_t> origins(n);
    for (size_t i = 0; i < n; ++i)
        origins[i] = i;

    static unsigned aux_time = 0;

    const auto lca = [&](size_t u, size_t v) {
        ++aux_time;

        while (u == 0 || times[u] != aux_time) {
            times[u] = aux_time;
            u = (mates[u] == 0 ? 0 : origins[parents[mates[u]]]);
            std::swap(u, v);
        }
        return u;
    };

    std::queue<size_t> q;

    const auto enqueue = [&](size_t u) {
        q.push(u);
        labels[u] = 1;
    };

    const auto blossom = [&](size_t u, size_t v, size_t x) {
        while (origins[u] != x) {
            parents[u] = v;
            v = mates[u];

            origins[u] = x;
            u = parents[v];

            origins[v] = x;
            if (labels[v] == 2)
                enqueue(v);
        }
    };

    const auto augment = [&](size_t u) {
        do {
            const size_t p = parents[u];
            const size_t v = mates[p];
            mates[u] = p;
            mates[p] = u;
            u = v;
        } while (u != 0);
    };

    enqueue(root);
    while (!q.empty()) {
        const size_t u = q.front();
        q.pop();

        for (const size_t v : g[u]) {
            if (labels[v] == 0) {
                parents[v] = u;
                if (mates[v] == 0)
                    return augment(v);

                enqueue(mates[v]);
                labels[v] = 2;
            }
            if (labels[v] == 1 && origins[u] != origins[v]) {
                const size_t x = lca(origins[u], origins[v]);
                blossom(v, u, x);
                blossom(u, v, x);
            }
        }
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    graph_t g(1 + n);
    for (unsigned u, v; std::cin >> u >> v; ) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    std::vector<size_t> mates(1 + n);
    {
        std::vector<unsigned> times(1 + n);
        std::vector<size_t> parents(1 + n);

        for (size_t i = 1; i <= n; ++i) {
            if (mates[i] == 0)
                search(g, times, parents, mates, i);
        }
    }

    std::vector<std::pair<unsigned, unsigned>> s;
    for (size_t i = 1; i <= n; ++i) {
        if (mates[i] != 0) {
            s.emplace_back(i, mates[i]);
            mates[mates[i]] = 0;
        }
    }

    std::cout << 2 * s.size() << '\n';
    for (const auto& [u, v] : s)
        std::cout << u << ' ' << v << '\n';

    return 0;
}
