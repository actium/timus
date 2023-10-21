#include <algorithm>
#include <iostream>
#include <vector>

using graph_t = std::vector<std::vector<size_t>>;

template <typename F>
void traverse(const graph_t& g, size_t u, std::vector<bool>& v, F&& callback)
{
    v[u] = true;

    for (const size_t x : g[u]) {
        if (!v[x])
            traverse(g, x, v, callback);
    }

    callback(u);
}

void solve(const graph_t& g, const graph_t& h)
{
    const size_t n = g.size();

    std::vector<size_t> p;
    {
        std::vector<bool> v(n);
        for (size_t i = 0; i < n; ++i) {
            if (!v[i]) {
                traverse(g, i, v, [&](size_t u) {
                    p.push_back(u);
                });
            }
        }
    }

    unsigned k = 0;
    {
        std::vector<bool> v(n);
        traverse(g, p.back(), v, [&](size_t) {
            ++k;
        });
    }

    if (k == n) {
        std::vector<unsigned> s;
        {
            std::vector<bool> v(n);
            traverse(h, p.back(), v, [&](size_t u) {
                s.push_back(1 + u);
            });
        }

        std::sort(s.begin(), s.end());

        for (const unsigned x : s)
            std::cout << x << ' ';
    }

    std::cout << 0 << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    graph_t g(n), h(n);
    for (size_t i = 0; i < n; ++i) {
        unsigned x;
        for (std::cin >> x; x != 0; std::cin >> x) {
            g[i].push_back(x-1);
            h[x-1].push_back(i);
        }
    }

    solve(g, h);

    return 0;
}
