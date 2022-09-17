#include <iostream>
#include <string>
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
    size_t n;
    std::cin >> n;

    unsigned d, a;
    std::cin >> d >> a;

    std::vector<std::string> g(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> g[i];

    std::vector<size_t> cs(n);
    for (size_t i = 0; i < n; ++i)
        cs[i] = i;

    std::vector<std::string> r(n, std::string(n, '0'));
    for (size_t i = 1; i < n; ++i) {
        for (size_t j = 0; j < i; ++j) {
            if (g[i][j] == '1' && merge(cs, i, j) == 0) {
                r[i][j] = 'd';
                r[j][i] = 'd';
            }
        }
    }
    for (size_t i = 1; i < n; ++i) {
        for (size_t j = 0; j < i; ++j) {
            if (merge(cs, i, j) == 1) {
                r[i][j] = 'a';
                r[j][i] = 'a';
            }
        }
    }

    unsigned long long s = 0;
    for (size_t i = 1; i < n; ++i) {
        for (size_t j = 0; j < i; ++j) {
            if (r[i][j] == 'd')
                s += d;

            if (r[i][j] == 'a')
                s += a;
        }
    }

    std::cout << s << '\n';
    for (const std::string& x : r)
        std::cout << x << '\n';

    return 0;
}
