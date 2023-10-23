#include <iostream>
#include <vector>

using graph_t = std::vector<std::vector<std::pair<size_t, unsigned>>>;

using integer = unsigned long long;

std::pair<unsigned, integer> traverse(const graph_t& g, size_t u, size_t p)
{
    std::pair<unsigned, integer> x = { 1, 0 };
    for (const std::pair<size_t, unsigned>& v : g[u]) {
        if (v.first != p) {
            const auto q = traverse(g, v.first, u);
            x.first += q.first;
            x.second += q.second + v.second * integer(g.size() - q.first) * q.first;
        }
    }
    return x;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    graph_t g(n);
    for (size_t i = 1; i < n; ++i) {
        unsigned a, b, c;
        std::cin >> a >> b >> c;

        g[a-1].emplace_back(b - 1, c);
        g[b-1].emplace_back(a - 1, c);
    }

    const double s = 2.0 * traverse(g, 0, 0).second;

    std::cout << std::fixed << s / n / (n - 1) << '\n';

    return 0;
}
