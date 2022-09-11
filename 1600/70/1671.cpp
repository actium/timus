#include <iostream>
#include <set>
#include <utility>
#include <vector>

size_t resolve(std::vector<size_t>& roots, size_t x)
{
    size_t root = x;
    while (root != roots[root])
        root = roots[root];

    while (roots[x] != root)
        x = std::exchange(roots[x], root);

    return root;
}

size_t merge(std::vector<size_t>& roots, size_t x, size_t y)
{
    const size_t rx = resolve(roots, x), ry = resolve(roots, y);
    if (rx != ry) {
        roots[ry] = rx;
        return 1;
    }
    return 0;
}

int main()
{
    size_t n, m;
    std::cin >> n >> m;

    std::vector<std::pair<unsigned, unsigned>> e(m);
    for (size_t i = 0; i < m; ++i)
        std::cin >> e[i].first >> e[i].second;

    size_t q;
    std::cin >> q;

    std::vector<unsigned> r(q);
    for (size_t i = 0; i < q; ++i)
        std::cin >> r[i];

    std::vector<size_t> roots(n);
    for (size_t i = 0; i < n; ++i)
        roots[i] = i;

    std::set<unsigned> s(r.cbegin(), r.cend());
    for (size_t i = 0; i < m; ++i) {
        if (s.count(1 + i) == 0)
            n -= merge(roots, e[i].first-1, e[i].second-1);
    }

    std::vector<size_t> c;
    for (auto it = r.crbegin(); it != r.crend(); ++it) {
        c.push_back(n);
        n -= merge(roots, e[*it-1].first-1, e[*it-1].second-1);
    }

    for (size_t i = 0; i < q; ++i)
        std::cout << c[q-1-i] << " \n"[i+1==q];

    return 0;
}
