#include <iostream>
#include <vector>

void solve(const std::vector<std::pair<unsigned, unsigned>>& r, unsigned s1, unsigned s2, unsigned t)
{
    const size_t k = r.size();

    std::vector<std::pair<size_t, size_t>> g[2000];
    for (size_t i = 0; i < k; ++i)
        g[r[i].first - 1].emplace_back(r[i].second - 1, i);

    std::vector<std::pair<size_t, unsigned>> q;
    std::vector<unsigned> v(2000, ~0u);

    const auto enqueue = [&](size_t x, unsigned d, size_t s) {
        if (v[x] == ~0u) {
            q.emplace_back(x, d);
            v[x] = s;
        }
    };

    enqueue(s1 - 1, 0, k);
    enqueue(s2 - 1, 0, k);
    for (size_t i = 0; i < q.size(); ++i) {
        const std::pair<size_t, unsigned> p = q[i];
        if (p.first == t - 1) {
            std::vector<unsigned> c;
            for (size_t x = t - 1; v[x] != k; x = r[v[x]].first - 1)
                c.push_back(v[x] + 1);

            std::cout << p.second << '\n';
            for (auto it = c.rbegin(); it != c.rend(); ++it)
                std::cout << *it << '\n';

            return;
        }

        for (const std::pair<size_t, size_t>& e : g[p.first])
            enqueue(e.first, p.second + 1, e.second);
    }

    std::cout << "IMPOSSIBLE" << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t k;
    std::cin >> k;

    std::vector<std::pair<unsigned, unsigned>> r(k);
    for (size_t i = 0; i < k; ++i)
        std::cin >> r[i].first >> r[i].second;

    unsigned t, s1, s2;
    std::cin >> t >> s1 >> s2;

    solve(r, s1, s2, t);

    return 0;
}
