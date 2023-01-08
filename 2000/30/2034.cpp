#include <iostream>
#include <queue>
#include <vector>

using graph_t = std::vector<std::vector<unsigned>>;

std::vector<unsigned> compute_distances(const graph_t& g, unsigned s)
{
    const size_t n = g.size();

    std::queue<unsigned> q;
    std::vector<bool> in_queue(n);

    const auto enqueue = [&](unsigned x) {
        if (!in_queue[x]) {
            q.push(x);
            in_queue[x] = true;
        }
    };

    const auto dequeue = [&] {
        const unsigned x = q.front();
        q.pop();
        in_queue[x] = false;
        return x;
    };

    std::vector<unsigned> d(n, ~unsigned(0));
    d[s] = 0;
    for (enqueue(s); !q.empty(); ) {
        const unsigned u = dequeue();
        for (const unsigned v : g[u]) {
            if (d[u] + 1 < d[v]) {
                d[v] = d[u] + 1;
                enqueue(v);
            }
        }
    }
    return d;
}

std::vector<unsigned> ds, df, dr;

void search(const graph_t& g, unsigned x, unsigned f, std::vector<int>& v)
{
    if (x == f)
        return;

    for (const unsigned u : g[x]) {
        if (ds[x] + 1 + df[u] != ds[f])
            continue;

        if (v[x] > v[u]) {
            v[u] = std::min<int>(v[x], dr[u]);
            search(g, u, f, v);
        }

        v[x] = std::max(v[x], v[u]);
    }
}

unsigned solve(const graph_t& g, unsigned s, unsigned f, unsigned r)
{
    const unsigned n = g.size();

    ds = compute_distances(g, s);
    df = compute_distances(g, f);
    dr = compute_distances(g, r);

    std::vector<int> v(n, -1);
    v[s] = dr[s];
    search(g, s, f, v);
    return v[f];
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n, m;
    std::cin >> n >> m;

    graph_t g(n);
    for (size_t i = 0; i < m; ++i) {
        unsigned u, v;
        std::cin >> u >> v;

        g[u-1].push_back(v-1);
        g[v-1].push_back(u-1);
    }

    unsigned s, f, r;
    std::cin >> s >> f >> r;

    std::cout << solve(g, s - 1, f - 1, r - 1) << '\n';

    return 0;
}
