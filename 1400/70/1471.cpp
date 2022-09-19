#include <iostream>
#include <vector>

constexpr size_t K = 16;

struct Context {
    unsigned t = 0;

    std::vector<unsigned> ti;
    std::vector<unsigned> to;
    std::vector<unsigned> d;
    std::vector<std::vector<size_t>> p;

    explicit Context(size_t n)
        : ti(n)
        , to(n)
        , d(n)
        , p(n, std::vector<size_t>(K))
    {}
};

class Graph {
public:
    explicit Graph(size_t size)
        : nodes_(size)
    {}

    void connect(size_t u, size_t v, unsigned w)
    {
        nodes_[u].emplace_back(v, w);
        nodes_[v].emplace_back(u, w);
    }

    void traverse(size_t v, size_t u, unsigned w, Context& q) const
    {
        q.ti[v] = q.t++;
        q.p[v][0] = u;
        q.d[v] = w;

        for (size_t i = 1; i < K; ++i)
            q.p[v][i] = q.p[q.p[v][i-1]][i-1];

        for (const std::pair<size_t, unsigned>& x : nodes_[v]) {
            if (x.first != u)
                traverse(x.first, v, w + x.second, q);
        }

        q.to[v] = q.t++;
    }

private:
    std::vector<std::vector<std::pair<size_t, unsigned>>> nodes_;

}; // class Graph

int main()
{
    size_t n;
    std::cin >> n;

    Graph g(n);
    for (size_t i = 1; i < n; ++i) {
        unsigned u, v, w;
        std::cin >> u >> v >> w;

        g.connect(u, v, w);
    }

    Context q(n);
    g.traverse(0, 0, 0, q);

    const auto is_parent = [&q](size_t a, size_t b) {
        return q.ti[a] <= q.ti[b] && q.to[a] >= q.to[b];
    };

    const auto lca = [&](size_t a, size_t b) {
        if (is_parent(a, b))
            return a;

        if (is_parent(b, a))
            return b;

        for (size_t i = K; i-- > 0; ) {
            if (!is_parent(q.p[a][i], b))
                a = q.p[a][i];
        }
        return q.p[a][0];
    };

    size_t m;
    for (std::cin >> m; m != 0; --m) {
        unsigned u, v;
        std::cin >> u >> v;

        const unsigned x = lca(u, v);
        std::cout << q.d[u] + q.d[v] - 2 * q.d[x] << '\n';
    }

    return 0;
}
