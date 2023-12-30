#include <iostream>
#include <queue>
#include <vector>

constexpr unsigned oo = ~0u;

struct Graph {
    struct Edge {
        size_t u;
        size_t v;
        unsigned d;
        bool active = true;
    };

    std::vector<Edge> edges;
    std::vector<std::vector<size_t>> links;

    void add_edge(size_t u, size_t v, unsigned d)
    {
        for (const size_t e : links[u]) {
            if (edges[e].u == v || edges[e].v == v) {
                edges[e].d = std::min(edges[e].d, d);
                return;
            }
        }

        links[u].push_back(edges.size());
        links[v].push_back(edges.size());
        edges.push_back({ u, v, d });
    }
};

struct State  {
    size_t x;
    unsigned d;
};

bool operator <(const State& lhs, const State& rhs)
{
    return lhs.d != rhs.d ? lhs.d > rhs.d : lhs.x > rhs.x;
}

unsigned search(const Graph& g, size_t s, size_t t, std::vector<size_t>& p)
{
    const size_t n = g.links.size();

    std::vector<unsigned> d(n, oo);
    d[s] = 0;

    std::priority_queue<State> q;
    q.push({ s, 0 });
    while (!q.empty()) {
        const State s = q.top();
        q.pop();

        if (s.d != d[s.x])
            continue;

        if (s.x == t)
            return s.d;

        for (const size_t e : g.links[s.x]) {
            if (!g.edges[e].active)
                continue;

            const size_t v = g.edges[e].u ^ g.edges[e].v ^ s.x;
            if (s.d + g.edges[e].d < d[v]) {
                d[v] = s.d + g.edges[e].d;
                p[v] = s.x;
                q.push({ v, d[v] });
            }
        }
    }
    return oo;
}

void solve(Graph& g)
{
    const size_t n = g.links.size();

    std::pair<unsigned, std::vector<size_t>> s;
    s.first = oo;
    for (Graph::Edge& e : g.edges) {
        e.active = false;

        std::vector<size_t> p(n, n);

        const unsigned w = search(g, e.u, e.v, p);
        if (w != oo && w + e.d < s.first) {
            s.first = w + e.d;
            s.second.clear();
            for (size_t x = e.v; x != n; x = p[x])
                s.second.push_back(x);
        }

        e.active = true;
    }

    if (s.first == oo) {
        std::cout << "No solution.";
    } else {
        for (const size_t p : s.second)
            std::cout << 1 + p << ' ';
    }
    std::cout << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    for (std::cin >> n; n != -1; std::cin >> n) {
        size_t m;
        std::cin >> m;

        Graph g;
        g.links.resize(n);
        for (size_t i = 0; i < m; ++i) {
            unsigned a, b, d;
            std::cin >> a >> b >> d;

            g.add_edge(a-1, b-1, d);
        }

        solve(g);
    }

    return 0;
}
