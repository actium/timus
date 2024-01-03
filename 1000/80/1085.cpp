#include <iostream>
#include <queue>
#include <set>
#include <vector>

constexpr unsigned oo = ~0u >> 8;

using graph_t = std::vector<std::vector<size_t>>;

struct Person {
    unsigned money;
    unsigned station;
    unsigned ticket;
};

const std::vector<unsigned> compute_costs(const graph_t& r, const graph_t& t, const Person& p)
{
    const size_t n = r.size();

    std::vector<unsigned> costs(n, oo);
    costs[p.station-1] = 0;

    std::set<size_t> v;
    std::queue<std::pair<size_t, unsigned>> q;

    const auto enqueue = [&](size_t route, unsigned cost) {
        if (p.ticket == 0 && p.money < cost)
            return;

        if (v.insert(route).second)
            q.emplace(route, cost);
    };

    for (const size_t route : t[p.station-1])
        enqueue(route, 4);

    while (!q.empty()) {
        const std::pair<size_t, unsigned> x = q.front();
        q.pop();

        for (const size_t station : r[x.first]) {
            costs[station] = std::min(costs[station], p.ticket == 0 ? x.second : 0);

            for (const size_t route : t[station])
                enqueue(route, x.second + 4);
        }
    }

    return costs;
}

void solve(const graph_t& r, const graph_t& t, const std::vector<Person>& p)
{
    const size_t n = r.size(), k = p.size();

    std::vector<unsigned> c(n);
    for (size_t i = 0; i < k; ++i) {
        const std::vector<unsigned> v = compute_costs(r, t, p[i]);
        for (size_t j = 0; j < n; ++j)
            c[j] += v[j];
    }

    size_t x = 0;
    for (size_t i = 1; i < n; ++i) {
        if (c[i] < c[x])
            x = i;
    }

    if (c[x] < oo)
        std::cout << 1 + x << ' ' << c[x] << '\n';
    else
        std::cout << 0 << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m;
    std::cin >> n >> m;

    std::vector<std::vector<size_t>> r(n), t(n);
    for (size_t i = 0; i < m; ++i) {
        size_t k;
        std::cin >> k;

        for (size_t j = 0; j < k; ++j) {
            unsigned x;
            std::cin >> x;

            r[i].push_back(x-1);
            t[x-1].push_back(i);
        }
    }

    size_t k;
    std::cin >> k;

    std::vector<Person> p(k);
    for (size_t i = 0; i < k; ++i)
        std::cin >> p[i].money >> p[i].station >> p[i].ticket;

    solve(r, t, p);

    return 0;
}
