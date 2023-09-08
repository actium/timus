#include <iostream>
#include <vector>

using Tree = std::vector<std::vector<size_t>>;

size_t find_root(const Tree& t)
{
    const size_t n = t.size();

    std::vector<size_t> p(n, n);
    for (size_t i = 0; i < n; ++i) {
        for (const size_t u : t[i])
            p[u] = i;
    }

    size_t i = 0;
    while (p[i] != n)
        ++i;

    return i;
}

std::pair<int, int> solve(const Tree& t, const std::vector<int>& r, size_t u)
{
    std::pair<int, int> s = std::make_pair(std::max(r[u], 0), 0);
    for (const size_t v : t[u]) {
        const auto c = solve(t, r, v);
        s.first += c.second;
        s.second += std::max(c.first, c.second);
    }
    return s;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<int> r(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> r[i];

    Tree t(n);
    while (true) {
        unsigned u, v;
        std::cin >> u >> v;

        if (u == 0 && v == 0)
            break;

        t[v-1].push_back(u-1);
    }

    const std::pair<int, int> s = solve(t, r, find_root(t));
    std::cout << std::max(s.first, s.second) << '\n';

    return 0;
}
