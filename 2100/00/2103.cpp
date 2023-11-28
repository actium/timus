#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

#include <cstdint>

constexpr unsigned oo = ~0u;

std::vector<unsigned> prepare(unsigned s, unsigned t)
{
    std::vector<unsigned> d;
    for (unsigned i = 2; i * i <= t; ++i) {
        if (t % i != 0)
            continue;

        d.push_back(i);

        if (i * i != t)
            d.push_back(t / i);
    }

    std::vector<unsigned> v;
    v.push_back(std::max(t - 1, 1u));
    v.push_back(t);
    v.push_back(t + 1);
    for (const unsigned x : d) {
        v.push_back(x - 1);
        v.push_back(x);
        v.push_back(x + 1);
    }
    for (unsigned i = 1; i <= 10; ++i)
        v.push_back(i);

    std::sort(v.begin(), v.end());
    v.erase(std::unique(v.begin(), v.end()), v.end());
    return v;
}

void solve(unsigned s, unsigned t)
{
    const std::vector<unsigned> v = prepare(s, t);

    const size_t n = v.size();

    std::vector<std::vector<unsigned>> w(n, std::vector<unsigned>(n, oo));
    for (size_t i = 1; i < n; ++i) {
        for (size_t j = 0; j < i; ++j) {
            const unsigned d = v[i] - v[j];
            w[j][i] = std::min(w[j][i], (v[i] % v[j] == 0 ? 0 : d));
            w[i][j] = std::min(w[i][j], d);
        }
    }

    std::set<std::pair<unsigned, uint16_t>> q;
    std::vector<unsigned> d(1 + n, oo);
    std::vector<uint16_t> p(1 + n, n);

    const auto enqueue = [&](size_t x, size_t s, unsigned w) {
        if (d[x] <= w)
            return;

        if (d[x] != oo)
            q.erase(std::make_pair(d[x], x));

        q.emplace(w, x);
        d[x] = w;
        p[x] = s;
    };

    enqueue(s - 1, n, 0);
    while (v[q.begin()->second] != t) {
        const std::pair<unsigned, uint16_t> x = *q.begin();
        q.erase(q.begin());

        for (size_t i = 0; i < n; ++i) {
            if (i != x.second)
                enqueue(i, x.second, x.first + w[x.second][i]);
        }
    }

    std::vector<unsigned> path;
    for (size_t u = q.begin()->second; u != n; u = p[u])
        path.push_back(v[u]);

    std::cout << q.begin()->first << '\n';
    std::cout << path.size() << '\n';
    for (auto it = path.rbegin(); it != path.rend(); ++it)
        std::cout << *it << ' ';
}

int main()
{
    unsigned s, t;
    std::cin >> s >> t;

    solve(s, t);

    return 0;
}
