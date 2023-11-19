#include <iostream>
#include <queue>
#include <vector>

constexpr unsigned oo = ~0u >> 1;

using graph_t = std::vector<std::vector<unsigned>>;

class MaxFlow {
public:
    MaxFlow(const graph_t& g, const std::vector<unsigned>& c)
        : graph_(g)
        , capacities_(c)
    {}

    unsigned operator ()(unsigned s, unsigned t, int ub)
    {
        unsigned v = 0;

        std::vector<unsigned> flow(graph_.size());
        while (ub != 0) {
            const std::vector<int> levels = bfs(s, flow);
            if (levels[t] == -1)
                break;

            std::vector<size_t> iters(graph_.size());
            for (unsigned f; f = dfs(s, t, ub, levels, iters, flow), f != 0; ) {
                v += f;
                ub -= f;
            }
        }

        return v;
    }

private:
    std::vector<int> bfs(unsigned s, const std::vector<unsigned>& flow)
    {
        std::vector<int> levels(graph_.size(), -1);
        {
            levels[s] = 0;

            std::queue<unsigned> q;
            q.push(s);
            while (!q.empty()) {
                const unsigned v = q.front();
                q.pop();

                for (const unsigned x : graph_[v]) {
                    if (flow[x] < capacities_[x] && levels[x] == -1) {
                        levels[x] = levels[v] + 1;
                        q.push(x);
                    }
                }
            }
        }
        return levels;
    }

    unsigned dfs(unsigned v, unsigned t, unsigned ub, const std::vector<int>& levels, std::vector<size_t>& iters, std::vector<unsigned>& flow)
    {
        if (v == t || ub == 0)
            return ub;

        for (size_t& i = iters[v]; i < graph_[v].size(); ++i) {
            const unsigned x = graph_[v][i];
            if (levels[x] != levels[v] + 1)
                continue;

            const unsigned d = dfs(x, t, std::min(capacities_[x] - flow[x], ub), levels, iters, flow);
            if (d != 0) {
                flow[x] += d;
                return d;
            }
        }
        return 0;
    }

private:
    const std::vector<std::vector<unsigned>>& graph_;
    const std::vector<unsigned>& capacities_;

}; // class MaxFlow

int main()
{
    unsigned k, n, m, s, t;
    std::cin >> k >> n >> m >> s >> t;

    std::vector<unsigned> c(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> c[i];

    c[s-1] = oo;
    c[t-1] = oo;

    graph_t g(n);
    for (size_t i = 0; i < m; ++i) {
        unsigned u, v;
        std::cin >> u >> v;

        g[u-1].push_back(v-1);
        g[v-1].push_back(u-1);
    }

    MaxFlow flow(g, c);
    std::cout << (k >= flow(s - 1, t - 1, oo) ? "YES" : "NO") << '\n';

    return 0;
}
