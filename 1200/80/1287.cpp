#include <iostream>
#include <string>
#include <vector>

#define UPDATE(r, c)        do {                                    \
                                const size_t x = (g[r][c] == 'S');  \
                                v[x] = std::max(v[x], ++d[x]);      \
                                d[x^1] = 0;                         \
                            } while (false);

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<std::string> g(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> g[i];

    unsigned v[2] = {};

    for (size_t i = 0; i < n; ++i) {
        unsigned d[2] = {};
        for (size_t j = 0; j < n; ++j)
            UPDATE(i, j);
    }
    for (size_t j = 0; j < n; ++j) {
        unsigned d[2] = {};
        for (size_t i = 0; i < n; ++i)
            UPDATE(i, j);
    }
    for (size_t i = 0; i < n; ++i) {
        unsigned d[2] = {};
        for (size_t j = 0; i + j < n; ++j)
            UPDATE(i + j, j);
    }
    for (size_t j = 1; j < n; ++j) {
        unsigned d[2] = {};
        for (size_t i = 0; i + j < n; ++i)
            UPDATE(i, i + j);
    }
    for (size_t i = 0; i < n; ++i) {
        unsigned d[2] = {};
        for (size_t j = 0; i + j < n; ++j)
            UPDATE(i + j, n - 1 - j);
    }
    for (size_t j = 1; j < n; ++j) {
        unsigned d[2] = {};
        for (size_t i = 0; i + j < n; ++i)
            UPDATE(i, n - 1 - (j + i));
    }

    if (v[0] == v[1]) {
        std::cout << '?' << '\n';
    } else {
        std::cout << "sS"[v[1] > v[0]] << '\n';
    }
    std::cout << std::max(v[0], v[1]) << '\n';

    return 0;
}
