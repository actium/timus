#include <iostream>
#include <queue>
#include <string>
#include <vector>

using graph_t = std::vector<std::vector<size_t>>;

std::vector<size_t> solve(const graph_t& g, const std::vector<std::string>& p, const std::string& t)
{
    const size_t n = g.size();

    std::vector<size_t> c(n, 141);
    c[0] = t.length();

    std::queue<std::pair<size_t, size_t>> q;
    std::vector<unsigned> d(n, 141);

    const auto enqueue = [&](size_t v, size_t k) {
        if (k < d[v]) {
            q.emplace(v, k);
            d[v] = k;
        }
    };

    enqueue(0, t.length());
    while (!q.empty()) {
        const std::pair<size_t, size_t> x = q.front();
        q.pop();

        for (const size_t v : g[x.first]) {
            c[v] = std::min(c[v], x.second);
            enqueue(v, x.second + 6 + p[x.first].length());
        }
    }

    std::vector<size_t> s;
    for (size_t i = 0; i < n; ++i) {
        if (c[i] <= 140)
            s.push_back(i);
    }
    return s;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<std::string> p;

    const auto index = [&](const std::string& q) {
        size_t x = 0;
        while (x < p.size() && p[x] != q)
            ++x;

        if (x == p.size())
            p.push_back(q);

        return x;
    };

    graph_t g(n);
    for (size_t i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;

        const size_t u = index(s);

        size_t k;
        std::cin >> k;

        for (size_t j = 0; j < k; ++j) {
            std::string t;
            std::cin >> t;

            g[u].push_back(index(t));
        }
    }

    std::cin.ignore();

    std::string t;
    std::getline(std::cin, t);

    const std::vector<size_t> s = solve(g, p, t);

    std::cout << s.size() << '\n';
    for (const size_t x : s)
        std::cout << p[x] << '\n';

    return 0;
}
