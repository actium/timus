#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using graph_t = std::vector<std::vector<std::pair<uint16_t, uint16_t>>>;

graph_t build_graph(const std::vector<std::string>& p, const unsigned c[10])
{
    const size_t n = p.size();

    graph_t g(n);

    std::unordered_map<std::string, uint16_t> x(n);
    for (size_t i = 0; i < n; ++i)
        x.emplace(p[i], i);

    const auto check = [&](const std::string& q, size_t i, unsigned d) {
        const auto it = x.find(q);
        if (it != x.end() && i < it->second) {
            g[i].emplace_back(it->second, d);
            g[it->second].emplace_back(i, d);
        }
    };

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < 10; ++j) {
            for (size_t k = 0; k < j; ++k) {
                if (p[i][k] == p[i][j])
                    continue;

                std::string t = p[i];
                std::swap(t[k], t[j]);
                check(t, i, c[k]);
            }

            for (char d = '0'; d <= '9'; ++d) {
                if (p[i][j] == d)
                    continue;

                std::string t = p[i];
                t[j] = d;
                check(t, i, c[j]);
            }
        }
    }

    return g;
}

void solve(const std::vector<std::string>& p, const unsigned c[10])
{
    const size_t n = p.size();

    const graph_t g = build_graph(p, c);

    std::vector<unsigned> d(n, ~0u);
    std::vector<unsigned> t(n, n);

    const auto compare = [&](uint16_t i, uint16_t j) {
        return d[i] > d[j];
    };

    std::priority_queue<uint16_t, std::vector<uint16_t>, decltype(compare)> q(compare);
    std::vector<bool> v(n);

    const auto enqueue = [&](size_t i, size_t p, unsigned c) {
        d[i] = c;
        t[i] = p;
        q.push(i);
    };

    const auto dequeue = [&] {
        const size_t x = q.top();
        q.pop();
        return x;
    };

    enqueue(0, n, 0);
    while (!q.empty()) {
        const size_t x = dequeue();
        if (v[x])
            continue;

        v[x] = true;
        if (x == n - 1)
            break;

        for (const auto& a : g[x]) {
            if (!v[a.first] && d[x] + a.second < d[a.first])
                enqueue(a.first, x, d[x] + a.second);
        }
    }

    if (v[n-1]) {
        std::cout << d[n-1] << '\n';

        std::vector<size_t> path;
        for (size_t i = n - 1; i != n; i = t[i])
            path.push_back(i);

        std::cout << path.size() << '\n';
        for (auto it = path.rbegin(); it != path.rend(); ++it)
            std::cout << *it + 1 << ' ';
    } else {
        std::cout << -1 << '\n';
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    unsigned c[10];
    for (size_t i = 0; i < 10; ++i)
        std::cin >> c[i];

    std::vector<std::string> s(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> s[i];

    solve(s, c);

    return 0;
}
