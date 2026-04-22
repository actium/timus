#include <iostream>
#include <queue>
#include <vector>

constexpr unsigned oo = ~0u;

struct State {
    unsigned target;
    unsigned distance;
};

void solve(const std::vector<std::vector<unsigned>>& routes, size_t m)
{
    const size_t n = routes.size();

    std::vector<std::vector<unsigned>> g(1+m);
    for (unsigned i = 0; i < n; ++i) {
        for (const unsigned x : routes[i])
            g[x].push_back(i);
    }

    std::vector<unsigned> distances(n, oo);
    std::vector<std::pair<unsigned, unsigned>> sources(n);

    std::queue<State> q;

    const auto enqueue = [&](unsigned target, unsigned distance, unsigned source, unsigned transit_station) {
        if (distance < distances[target]) {
            distances[target] = distance;
            sources[target] = { source, transit_station };
            q.push({ target, distance });
        }
    };

    enqueue(0, 0, 0, 0);

    while (!q.empty() && distances[n-1] == oo) {
        const State p = q.front();
        q.pop();

        for (const unsigned station : routes[p.target]) {
            for (const unsigned target : g[station])
                enqueue(target, p.distance + 1, p.target, station);
        }
    }

    if (distances[n-1] != oo) {
        std::vector<unsigned> path;
        for (unsigned x = n-1; x != 0; x = sources[x].first)
            path.push_back(sources[x].second);

        std::cout << path.size() - 1 << '\n';
        for (auto it = path.rbegin(); it != path.rend(); ++it)
            std::cout << *it << ' ';
    } else {
        std::cout << -1 << '\n';
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m;
    std::cin >> n >> m;

    std::vector<std::vector<unsigned>> routes(1+n+1);
    for (size_t i = 1; i <= n; ++i) {
        size_t k;
        std::cin >> k;

        routes[i].resize(k);

        for (size_t j = 0; j < k; ++j)
            std::cin >> routes[i][j];
    }

    unsigned a, b;
    std::cin >> a >> b;

    routes[0].push_back(a);
    routes[n+1].push_back(b);

    solve(routes, m);

    return 0;
}
