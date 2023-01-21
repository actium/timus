#include <iostream>
#include <utility>
#include <vector>

int main()
{
    size_t m, n;
    std::cin >> m >> n;

    std::vector<size_t> r(m);
    for (size_t i = 0; i < m; ++i)
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

    unsigned k = 0;
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            unsigned x;
            std::cin >> x;

            if (--x != i) {
                merge(i, x);
                ++k;
            }
        }
    }

    std::vector<bool> t(m);
    for (size_t i = 0; i < m; ++i) {
        const size_t r = resolve(i);
        if (r != i && !t[r]) {
            ++k;
            t[r] = true;
        }
    }

    std::cout << k - (k != 0) << '\n';

    return 0;
}
    