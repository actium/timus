#include <iostream>
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
        roots[rx] = ry;
        return 1;
    }
    return 0;
}

int main()
{
    size_t n, k, m;
    std::cin >> n >> k >> m;

    std::vector<size_t> roots(n);
    for (size_t i = 0; i < n; ++i)
        roots[i] = i;

    for (size_t i = 0; i < k; ++i) {
        unsigned u, v;
        std::cin >> u >> v;

        n -= merge(roots, u-1, v-1);
    }

    for (size_t i = 0; i < m; ++i) {
        unsigned u, v;
        std::cin >> u >> v;
    }

    std::cout << n - 1 << '\n';

    return 0;
}
