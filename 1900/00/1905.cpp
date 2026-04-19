#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

struct Edge {
    unsigned route_id;
    size_t target;
};

using graph_t = std::vector<std::vector<Edge>>;

struct Route {
    unsigned u;
    unsigned v;

    unsigned s;
    unsigned t;
};

bool search(const graph_t& g, size_t u, size_t x, std::vector<bool>& visited, std::vector<unsigned>& p)
{
    if (u == x)
        return true;

    visited[u] = true;
    for (const auto& e : g[u]) {
        if (visited[e.target])
            continue;

        p.push_back(e.route_id);
        if (search(g, e.target, x, visited, p))
            return true;

        p.pop_back();
    }
    visited[false];
    return false;
}

void solve(size_t n, const std::vector<Route>& routes, unsigned u, unsigned v, unsigned s, unsigned t)
{
    std::vector<std::vector<unsigned>> timestamps(1 + n);
    for (const auto& r : routes) {
        timestamps[r.u].push_back(r.s);
        timestamps[r.v].push_back(r.t);
    }
    timestamps[u].push_back(s);
    timestamps[v].push_back(t);

    std::map<std::pair<unsigned, unsigned>, size_t> index;
    for (size_t i = 1; i <= n; ++i) {
        std::sort(timestamps[i].begin(), timestamps[i].end());
        timestamps[i].erase(std::unique(timestamps[i].begin(), timestamps[i].end()), timestamps[i].end());

        for (const unsigned ts : timestamps[i])
            index.emplace(std::make_pair(i, ts), index.size());
    }

    const auto vertex_id = [&](unsigned planet_id, unsigned timestamp) {
        return index[{ planet_id, timestamp }];
    };

    graph_t g(index.size());
    for (unsigned i = 1; i <= n; ++i) {
        for (size_t j = 1; j < timestamps[i].size(); ++j) {
            const size_t source = vertex_id(i, timestamps[i][j-1]);
            const size_t target = vertex_id(i, timestamps[i][j]);
            g[source].push_back({ 0, target });
        }
    }

    for (size_t i = 0; i < routes.size(); ++i) {
        const size_t source = vertex_id(routes[i].u, routes[i].s);
        const size_t target = vertex_id(routes[i].v, routes[i].t);
        g[source].push_back({ static_cast<unsigned>(1 + i), target });
    }

    std::vector<unsigned> p;
    if (std::vector<bool> visited(g.size()); search(g, vertex_id(u, s), vertex_id(v, t), visited, p)) {
        p.erase(std::remove(p.begin(), p.end(), 0), p.end());

        std::cout << p.size() << '\n';
        for (const unsigned x : p)
            std::cout << x << ' ';
    } else {
        std::cout << "Impossible" << '\n';
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m;
    std::cin >> n >> m;

    std::vector<Route> routes(m);
    for (Route& r : routes)
        std::cin >> r.u >> r.v >> r.s >> r.t;

    unsigned u, v, s, t;
    std::cin >> u >> v >> s >> t;

    solve(n, routes, u, v, s, t);

    return 0;
}
