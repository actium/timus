#include <iostream>
#include <map>
#include <vector>

using integer = unsigned long long;

using edge_t = std::pair<unsigned, unsigned>;
using graph_t = std::vector<std::vector<edge_t>>;

constexpr unsigned M = 18;

std::vector<unsigned> depths;
std::vector<unsigned> labels;
std::vector<integer> weights;

std::vector<std::vector<unsigned>> jumps;

void prepare(const graph_t& g, unsigned u, unsigned p)
{
    static unsigned t = 0;

    labels[u] = t++;

    jumps[u].resize(M);
    jumps[u][0] = p;
    for (unsigned i = 1; i < M; ++i)
        jumps[u][i] = jumps[jumps[u][i-1]][i-1];

    for (const auto& [v, w] : g[u]) {
        if (v != p) {
            depths[v] = depths[u] + 1;
            weights[v] = weights[u] + w;
            prepare(g, v, u);
        }
    }
}

unsigned lca(unsigned u, unsigned v)
{
    if (depths[v] < depths[u])
        std::swap(u, v);

    for (unsigned i = M; i-- > 0; ) {
        if (depths[jumps[v][i]] >= depths[u])
            v = jumps[v][i];
    }

    if (v == u)
        return v;

    for (unsigned i = M; i-- > 0; ) {
        if (jumps[v][i] != jumps[u][i]) {
            v = jumps[v][i];
            u = jumps[u][i];
        }
    }
    return jumps[v][0];
}

integer weight(unsigned u, unsigned v)
{
    return weights[u] + weights[v] - 2 * weights[lca(u, v)];
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    graph_t g(n);
    for (size_t i = 1; i < n; ++i) {
        unsigned u, v, w;
        std::cin >> u >> v >> w;

        g[u-1].emplace_back(v-1, w);
        g[v-1].emplace_back(u-1, w);
    }

    depths.resize(n);
    labels.resize(n);
    weights.resize(n);
    jumps.resize(n);

    prepare(g, 0, 0);

    std::map<unsigned, unsigned> s;

    const auto select_adjacents = [&](unsigned x) {
        const auto it = s.lower_bound(labels[x]);
        const unsigned prev = (it == s.begin() ? s.rbegin()->second : std::prev(it)->second);

        const auto jt = s.upper_bound(labels[x]);
        const unsigned next = (jt == s.end() ? s.begin()->second : jt->second);

        return std::make_pair(prev, next);
    };

    integer W = 0;

    const auto insert = [&](unsigned x) {
        if (!s.empty()) {
            const std::pair<unsigned, unsigned> r = select_adjacents(x);

            W -= weight(r.first, r.second);
            W += weight(r.first, x);
            W += weight(x, r.second);
        }
        s.emplace(labels[x], x);
    };

    const auto remove = [&](unsigned x) {
        const std::pair<unsigned, unsigned> r = select_adjacents(x);

        W -= weight(r.first, x);
        W -= weight(x, r.second);
        W += weight(r.first, r.second);

        s.erase(labels[x]);
    };

    size_t q;
    std::cin >> q;

    for (size_t i = 0; i < q; ++i) {
        char t;
        std::cin >> t;

        unsigned x;
        std::cin >> x;

        t == '+' ? insert(x-1) : remove(x-1);

        std::cout << W / 2 << '\n';
    }

    return 0;
}
