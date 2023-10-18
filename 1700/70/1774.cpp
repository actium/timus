#include <iostream>
#include <queue>
#include <vector>

constexpr unsigned oo = ~0u >> 1;

class MaxFlow {
    struct Edge {
        size_t u;
        size_t v;

        int c;
        int f;
    };

public:
    explicit MaxFlow(size_t size)
        : graph_(size)
    {}

    void add_edge(size_t u, size_t v, int c)
    {
        graph_[u].push_back(edges_.size());
        edges_.push_back({u, v, c, 0});
        graph_[v].push_back(edges_.size());
        edges_.push_back({v, u, 0, 0});
    }

    int operator ()(size_t s, size_t t, int ub)
    {
        int v = 0;
        while (ub != 0) {
            const std::vector<int> levels = BFS(s);
            if (levels[t] == -1)
                break;

            std::vector<size_t> iters(graph_.size());
            for (int f; f = DFS(s, t, ub, levels, iters), f != 0; ) {
                v += f;
                ub -= f;
            }
        }
        return v;
    }

    template <typename F>
    void visit(F&& f) const
    {
        for (const Edge& e : edges_) {
            if (e.c != 0 && e.f == 1)
                f(e.u, e.v);
        }
    }

private:
    std::vector<int> BFS(size_t s)
    {
        std::vector<int> levels(graph_.size(), -1);
        {
            levels[s] = 0;

            std::queue<size_t> q;
            q.push(s);
            while (!q.empty()) {
                const size_t v = q.front();
                q.pop();

                for (const size_t x : graph_[v]) {
                    const Edge& e = edges_[x];
                    if (e.f < e.c && levels[e.v] == -1) {
                        levels[e.v] = levels[v] + 1;
                        q.push(e.v);
                    }
                }
            }
        }
        return levels;
    }

    int DFS(size_t v, size_t t, int ub, const std::vector<int>& levels, std::vector<size_t>& iters)
    {
        if (v == t || ub == 0)
            return ub;

        for (size_t& i = iters[v]; i < graph_[v].size(); ++i) {
            Edge& e = edges_[graph_[v][i]];
            if (levels[e.v] != levels[v] + 1)
                continue;

            const int d = DFS(e.v, t, std::min(e.c - e.f, ub), levels, iters);
            if (d != 0) {
                e.f += d;
                edges_[graph_[v][i] ^ 1].f -= d;
                return d;
            }
        }
        return 0;
    }

private:
    std::vector<Edge> edges_;
    std::vector<std::vector<size_t>> graph_;

}; // class MaxFlow

void solve(std::vector<std::pair<unsigned, unsigned>>& ts, size_t k)
{
    const size_t n = ts.size();

    std::vector<unsigned> x(1 + 2000, oo), y(1 + 2000);
    for (const std::pair<unsigned, unsigned>& e : ts) {
        for (unsigned i = e.first; i < e.first + e.second; ++i)
            x[i] = 0;
    }

    size_t m = 0;
    for (size_t i = 0; i <= 2000; ++i) {
        if (x[i] == 0) {
            x[i] = m;
            y[m] = i;
            ++m;
        }
    }

    MaxFlow f(1 + n + m + 1);
    for (size_t i = 0; i < n; ++i) {
        f.add_edge(0, 1 + i, 2);

        for (unsigned t = ts[i].first; t < ts[i].first + ts[i].second; ++t)
            f.add_edge(1 + i, 1 + n + x[t], 1);
    }
    for (size_t i = 0; i < m; ++i)
        f.add_edge(1 + n + i, 1 + n + m, k);

    const unsigned v = f(0, 1 + n + m, 2 * n);
    if (v != 2 * n) {
        std::cout << "No" << '\n';
    } else {
        std::vector<std::pair<unsigned, unsigned>> rs(n, {oo, oo});
        f.visit([&](size_t u, size_t v) {
            if (u < 1 || u > n || v < 1 + n || v > n + m)
                return;

            std::swap(rs[u-1].first, rs[u-1].second);
            rs[u-1].second = y[v - n - 1];
        });

        std::cout << "Yes" << '\n';
        for (size_t i = 0; i < n; ++i)
            std::cout << rs[i].first << ' ' << rs[i].second << '\n';
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, k;
    std::cin >> n >> k;

    std::vector<std::pair<unsigned, unsigned>> ts(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> ts[i].first >> ts[i].second;

    solve(ts, k);

    return 0;
}
