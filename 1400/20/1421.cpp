#include <iostream>
#include <numeric>
#include <queue>
#include <vector>

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
        for (const Edge& e : edges_)
            f(e.u, e.v, e.f);
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

void solve(std::vector<unsigned>& sr, std::vector<unsigned>& sc)
{
    const size_t n = sr.size(), m = 1 + n, k = m + n;

    MaxFlow mf(k + 1);
    for (size_t i = 0; i < n; ++i) {
        mf.add_edge(0, 1 + i, sr[i]);
        mf.add_edge(m + i, k, sc[i]);

        for (size_t j = 0; j < n; ++j)
            mf.add_edge(1 + i, m + j, 100);
    }

    const unsigned s = std::accumulate(sr.begin(), sr.end(), 0);
    if (mf(0, k, s) != s) {
        std::cout << "NO" << '\n';
        return;
    }

    std::vector<std::vector<unsigned>> x(n, std::vector<unsigned>(n));
    mf.visit([&](size_t u, size_t v, unsigned f) {
        if (u == 0 || u > n || v < m || v == k)
            return;

        x[u-1][v-m] = f;
    });

    std::cout << "YES" << '\n';
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j)
            std::cout << x[i][j] << ' ';

        std::cout << '\n';
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<unsigned> sr(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> sr[i];

    std::vector<unsigned> sc(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> sc[i];

    solve(sr, sc);

    return 0;
}
