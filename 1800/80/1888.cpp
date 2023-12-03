#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using graph_t = std::vector<std::vector<unsigned>>;

bool search(const graph_t& g, size_t x, std::vector<unsigned>& r, int d)
{
    std::queue<size_t> q;
    q.push(x);
    while (!q.empty()) {
        const size_t x = q.front();
        q.pop();

        for (const size_t u : g[x]) {
            if (r[u] == 0) {
                r[u] = r[x] + d;
                q.push(u);
            }

            if ((r[x] + r[u]) % 2 != 1)
                return false;
        }
    }
    return true;
}

unsigned evaluate(const std::vector<unsigned>& r)
{
    const auto d = std::minmax_element(r.begin(), r.end());
    return *d.second - *d.first;
}

void solve(const graph_t& g)
{
    const size_t n = g.size();

    std::vector<unsigned> r(n);
    size_t k = 0;
    for (size_t i = 0; i < n; ++i) {
        if (r[i] != 0)
            continue;

        r[i] = (i == 0 ? 1 : 50);

        if (!search(g, i, r, i == 0 ? 1 : -1)) {
            std::cout << "-1" << '\n';
            return;
        }

        ++k;
    }

    if (k == 1) {
        std::pair<unsigned, size_t> b = { evaluate(r), 0 };
        for (size_t i = 1; i < n; ++i) {
            r.assign(n, 0);
            r[i] = 1;
            search(g, i, r, 1);
            b = std::max(b, std::make_pair(evaluate(r), i));
        }

        r.assign(n, 0);
        r[b.second] = 1;
        search(g, b.second, r, 1);
    }

    std::cout << evaluate(r) << '\n';
    for (size_t i = 0; i < n; ++i)
        std::cout << r[i] << ' ';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, p;
    std::cin >> n >> p;

    graph_t g(p);
    for (size_t i = 0; i < n; ++i) {
        unsigned u, v;
        std::cin >> u >> v;

        g[u-1].push_back(v-1);
        g[v-1].push_back(u-1);
    }

    solve(g);

    return 0;
}
