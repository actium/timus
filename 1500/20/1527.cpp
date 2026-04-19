#include <iostream>
#include <queue>
#include <vector>

constexpr unsigned oo = 1000001;

struct Edge {
    unsigned u;
    unsigned v;

    unsigned c;
    unsigned d;
    unsigned h;
};

struct State {
    unsigned x;
    unsigned c;
    unsigned d;
};

bool operator <(const State& lhs, const State& rhs)
{
    return lhs.d != rhs.d ? lhs.d > rhs.d : lhs.c > rhs.c;
}

void solve(size_t n, const std::vector<Edge>& edges, unsigned s, unsigned t, unsigned c, unsigned d)
{
    const size_t m = edges.size();

    std::vector<std::vector<size_t>> g(1 + n);
    for (size_t i = 0; i < m; ++i)
        g[edges[i].u].push_back(i);

    const auto check = [&](unsigned h) {
        unsigned cost_upper_bound = 0;
        for (const auto& e : edges) {
            if (e.h <= h)
                cost_upper_bound += e.c;
        }

        cost_upper_bound = std::min(cost_upper_bound, c);

        std::vector<std::vector<unsigned>> distances(1 + n, std::vector<unsigned>(1 + cost_upper_bound, oo));
        std::vector<std::vector<size_t>> sources(1 + n, std::vector<size_t>(1 + cost_upper_bound));

        std::priority_queue<State> q;

        const auto enqueue = [&](unsigned x, unsigned c, unsigned d, size_t p) {
            if (c <= cost_upper_bound && d < distances[x][c]) {
                distances[x][c] = d;
                sources[x][c] = p;
                q.push({ x, c, d });
            }
        };

        enqueue(s, 0, 0, m);
        while (!q.empty()) {
            const State p = q.top();
            q.pop();

            if (p.d != distances[p.x][p.c])
                continue;

            for (const auto u : g[p.x]) {
                const Edge& e = edges[u];
                if (e.h <= h)
                    enqueue(e.v, p.c + e.c, p.d + e.d, u);
            }
        }

        unsigned cost = 0;
        while (cost <= cost_upper_bound && distances[t][cost] > d)
            ++cost;

        std::vector<size_t> path;
        if (cost > cost_upper_bound || distances[t][cost] > d)
            return std::make_pair(false, path);

        for (unsigned x = t; x != s; ) {
            const size_t road_id = sources[x][cost];
            path.push_back(road_id);
            cost -= edges[road_id].c;
            x = edges[road_id].u;
        }
        return std::make_pair(true, path);
    };

    int lb = -1, ub = oo;
    while (lb + 1 < ub) {
        const int mid = (lb + ub) / 2;
        (check(mid).first ? ub : lb) = mid;
    }

    if (ub == oo) {
        std::cout << -1 << '\n';
    } else {
        std::cout << ub << '\n';

        const std::vector<size_t> path = check(ub).second;

        std::cout << path.size() << '\n';
        for (auto it = path.rbegin(); it != path.rend(); ++it)
            std::cout << *it + 1 << ' ';
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m;
    std::cin >> n >> m;

    unsigned s, t;
    std::cin >> s >> t;

    unsigned c, d;
    std::cin >> c >> d;

    std::vector<Edge> edges(m);
    for (Edge& e : edges)
        std::cin >> e.u >> e.v >> e.c >> e.d >> e.h;

    solve(n, edges, s, t, c, d);

    return 0;
}
