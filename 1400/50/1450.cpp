#include <iostream>
#include <queue>
#include <vector>

int main()
{
    size_t n, m;
    std::cin >> n >> m;

    std::vector<std::vector<std::pair<size_t, unsigned>>> g(n);
    for (size_t i = 0; i < m; ++i) {
        unsigned a, b, c;
        std::cin >> a >> b >> c;

        g[a-1].emplace_back(b-1, c);
    }

    unsigned s, f;
    std::cin >> s >> f;

    std::vector<unsigned> c(n);
    {
        std::queue<size_t> q;
        for (q.push(s-1); !q.empty(); q.pop()) {
            const size_t x = q.front();
            for (const auto& e : g[x]) {
                if (c[x] + e.second > c[e.first]) {
                    c[e.first] = c[x] + e.second;
                    q.push(e.first);
                }
            }
        }
    }

    if (c[f-1] == 0) {
        std::cout << "No solution" << '\n';
    } else {
        std::cout << c[f-1] << '\n';
    }

    return 0;
}
