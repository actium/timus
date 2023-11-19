#include <iostream>
#include <queue>
#include <vector>

constexpr unsigned oo = ~0u >> 1;

class MaxFlow {
    struct Edge {
        unsigned t;
        unsigned c;
        unsigned r;
    };

public:
    explicit MaxFlow(unsigned size)
        : graph_(size)
    {}

    void add_edge(unsigned s, unsigned t, unsigned c)
    {
        const auto sx = graph_[s].size(), tx = graph_[t].size();
        graph_[s].push_back({ t, c, static_cast<unsigned>(tx) });
        graph_[t].push_back({ s, 0, static_cast<unsigned>(sx) });
    }

    unsigned operator ()(unsigned s, unsigned t)
    {
        unsigned v = 0;
        while (true) {
            const std::vector<int> levels = BFS(s);
            if (levels[t] == -1)
                break;

            std::vector<size_t> iters(graph_.size());
            for (unsigned f; f = DFS(s, t, oo, levels, iters), f != 0; v += f);
        }
        return v;
    }

private:
    std::vector<int> BFS(unsigned s)
    {
        std::vector<int> levels(graph_.size(), -1);
        {
            levels[s] = 0;

            std::queue<unsigned> q;
            q.push(s);
            while (!q.empty()) {
                const unsigned v = q.front();
                q.pop();

                for (const Edge& e : graph_[v]) {
                    if (e.c != 0 && levels[e.t] == -1) {
                        levels[e.t] = levels[v] + 1;
                        q.push(e.t);
                    }
                }
            }
        }
        return levels;
    }

    unsigned DFS(unsigned v, unsigned t, unsigned ub, const std::vector<int>& levels, std::vector<size_t>& iters)
    {
        if (v == t)
            return ub;

        for (size_t& i = iters[v]; i < graph_[v].size(); ++i) {
            Edge& e = graph_[v][i];
            if (e.c != 0 && levels[v] + 1 == levels[e.t]) {
                const unsigned d = DFS(e.t, t, std::min(e.c, ub), levels, iters);
                if (d != 0) {
                    e.c -= d;
                    graph_[e.t][e.r].c += d;
                    return d;
                }
            }
        }
        return 0;
    }

private:
    std::vector<std::vector<Edge>> graph_;

}; // class MaxFlow

int main()
{
    unsigned k, n, m, s, t;
    std::cin >> k >> n >> m >> s >> t;

    std::vector<unsigned> c(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> c[i];

    std::vector<std::vector<unsigned>> g(n);
    for (size_t i = 0; i < m; ++i) {
        unsigned u, v;
        std::cin >> u >> v;

        g[u-1].push_back(v-1);
        g[v-1].push_back(u-1);
    }

    c[--s] = oo;
    c[--t] = oo;

    MaxFlow flow(2 * n);
    {
        for (unsigned i = 0; i < n; ++i)
            flow.add_edge(2*i, 2*i+1, c[i]);

        for (unsigned u = 0; u < n; ++u) {
            for (const unsigned v : g[u])
                flow.add_edge(2*u+1, 2*v, oo);
        }
    }

    std::cout << (flow(2*s, 2*t+1) <= k ? "YES" : "NO") << '\n';

    return 0;
}
