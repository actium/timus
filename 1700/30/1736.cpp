#include <iostream>
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
        for (const Edge& e : edges_) {
            if (e.c != 0 && e.f < 4)
                f(e.u, e.v, e.f);
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

void solve(const std::vector<unsigned>& s)
{
    const size_t n = s.size();

    MaxFlow mf(2 + n + n);
    for (size_t i = 0; i < n; ++i) {
        mf.add_edge(0, 1 + i, 3 * (n - 1 - i));

        mf.add_edge(1 + i, 1 + n + i, 3 * (n - 1 - i));
        for (size_t j = i + 1; j < n; ++j)
            mf.add_edge(1 + i, 1 + n + j, 3);

        mf.add_edge(1 + n + i, 1 + n + n, s[i]);
    }

    unsigned b = 0;
    for (size_t i = 0; i < n; ++i)
        b += s[i];

    const unsigned v = mf(0, 1 + n + n, b);
    if (v != b) {
        std::cout << "INCORRECT" << '\n';
    } else {
        std::cout << "CORRECT" << '\n';

        mf.visit([n](size_t u, size_t v, int f) {
            if (u > v) {
                std::swap(u, v);
                f = 3 - f;
            }

            v -= n;

            if (u != 0 && v != 1 + n && u != v) {
                static constexpr const char* t[] = { " > ", " >= ", " <= ", " < " };
                std::cout << u << t[f] << v << '\n';
            }
        });
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<unsigned> s(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> s[i];

    solve(s);

    return 0;
}
