#include <iostream>
#include <numeric>
#include <queue>
#include <vector>

struct Gear {
    unsigned k;
    std::vector<size_t> c;

    std::pair<int, unsigned> v = { 0, 1 };
};

void solve(std::vector<Gear>& g, size_t u, unsigned v)
{
    std::queue<size_t> q;

    const auto enqueue = [&](size_t x, const std::pair<int, unsigned>& v) {
        if (g[x].v.first == 0) {
            g[x].v = v;
            q.push(x);
        }
    };

    enqueue(u, std::make_pair(v, 1));
    while (!q.empty()) {
        const size_t x = q.front();
        q.pop();

        for (const size_t u : g[x].c) {
            const int p = g[x].v.first * g[x].k, q = g[x].v.second * g[u].k, d = std::gcd(p, q);
            enqueue(u, std::make_pair(-p / d, q / d));
        }
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<Gear> g(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> g[i].k;

        unsigned x;
        while (std::cin >> x && x != 0)
            g[i].c.push_back(x - 1);
    }

    unsigned s, v;
    std::cin >> s >> v;

    solve(g, s - 1, v);

    for (size_t i = 0; i < n; ++i)
        std::cout << g[i].v.first << '/' << g[i].v.second << '\n';

    return 0;
}
