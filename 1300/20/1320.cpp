#include <iostream>
#include <utility>
#include <vector>

unsigned solve(unsigned n, const std::vector<std::pair<size_t, size_t>>& e)
{
    std::vector<size_t> r(n);
    for (size_t i = 0; i < n; ++i)
        r[i] = i;

    const auto resolve = [&](size_t x) {
        size_t root = x;
        while (root != r[root])
            root = r[root];

        while (r[x] != root)
            x = std::exchange(r[x], root);

        return root;
    };

    const auto merge = [&](size_t x, size_t y) {
        const size_t rx = resolve(x), ry = resolve(y);
        if (rx != ry)
            r[rx] = ry;
    };

    for (const std::pair<size_t, size_t>& q : e)
        merge(q.first, q.second);

    std::vector<unsigned> k(n);
    for (const std::pair<size_t, size_t>& q : e)
        ++k[resolve(q.first)];

    for (size_t i = 0; i < n; ++i) {
        if (k[i] % 2 != 0)
            return 0;
    }
    return 1;
}

int main()
{
    unsigned n = 0;

    std::vector<std::pair<size_t, size_t>> e;
    for (unsigned u, v; std::cin >> u >> v; ) {
        e.emplace_back(u - 1, v - 1);
        n = std::max(n, u);
        n = std::max(n, v);
    }

    std::cout << solve(n, e) << '\n';

    return 0;
}
