#include <algorithm>
#include <iostream>
#include <vector>

using graph_t = std::vector<std::vector<size_t>>;

constexpr size_t N = 32767;

void compute_distances(const graph_t& g, size_t s, std::vector<unsigned>& d)
{
    std::vector<size_t> q;

    const auto enqueue = [&](size_t x, unsigned v) {
        if (v < d[x]) {
            d[x] = v;
            q.push_back(x);
        }
    };

    enqueue(s, 0);
    for (size_t i = 0; i < q.size(); ++i) {
        const size_t u = q[i];

        for (const size_t v : g[u])
            enqueue(v, d[u] + 1);
    }
}

void search(const graph_t& g, const std::vector<unsigned>& d, size_t u, std::vector<bool>& v, std::vector<size_t>& s)
{
    s.push_back(u);

    v[u] = true;

    for (const size_t x : g[u]) {
        if (!v[x] && d[x] == d[u] + 1)
            search(g, d, x, v, s);
    }
}

void solve(const graph_t& g, const std::vector<unsigned>& x)
{
    const size_t n = g.size();

    std::vector<unsigned> d(n, ~0u);
    compute_distances(g, x[0] - 1, d);

    std::vector<bool> v(n);
    for (const unsigned q : x)
        v[q-1] = true;

    std::vector<size_t> s;
    search(g, d, x.back() - 1, v, s);

    std::sort(s.begin(), s.end());
    for (const size_t x : s)
        std::cout << 1 + x << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    graph_t g(N);
    for (size_t i = 0; i < n; ++i) {
        size_t k;
        std::cin >> k;

        unsigned u;
        std::cin >> u;

        for (size_t j = 1; j < k; ++j) {
            unsigned v;
            std::cin >> v;

            g[u-1].push_back(v-1);
            g[v-1].push_back(u-1);

            u = v;
        }
    }

    size_t m;
    std::cin >> m;

    std::vector<unsigned> x(m);
    for (size_t i = 0; i < m; ++i)
        std::cin >> x[i];

    solve(g, x);

    return 0;
}
