#include <iostream>
#include <vector>

using integer = unsigned long long;

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m;
    std::cin >> n >> m;

    std::vector<std::vector<unsigned>> a(n, std::vector<unsigned>(m));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j)
            std::cin >> a[i][j];
    }

    std::vector<std::vector<integer>> ps(1+n, std::vector<integer>(1+m));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j)
            ps[i+1][j+1] = ps[i][j+1] + ps[i+1][j] - ps[i][j] + a[i][j];
    }

    const auto query = [&](size_t sr, size_t sc, size_t tr, size_t tc) {
        return ps[tr][tc] - ps[tr][sc-1] - ps[sr-1][tc] + ps[sr-1][sc-1];
    };

    std::vector<std::vector<integer>> ds(1+n, std::vector<integer>(1+n+m));
    for (size_t i = 1; i <= n; ++i) {
        for (size_t j = 2; j <= i; ++j)
            ds[i][j] = ds[i-1][j];

        for (size_t j = i+1; j <= n+m; ++j)
            ds[i][j] = ds[i-1][j] + query(i, 1, i, std::min(j - i, m));
    }

    size_t q;
    std::cin >> q;

    while (q-- != 0) {
        unsigned k;
        std::cin >> k;

        std::pair<integer, std::pair<size_t, size_t>> v = {};
        for (size_t i = 1; i <= n; ++i) {
            for (size_t j = 1; j <= m; ++j) {
                const auto x = std::min(i + j + k, n + m), y = std::min(x - j + 1, n);

                const auto t = ds[y][x] - ds[i-1][x] + ps[i-1][j-1] - ps[y][j-1];
                v = std::max(v, std::make_pair(t, std::make_pair(i, j)));
            }
        }
        std::cout << v.first << ' ' << v.second.first << ' ' << v.second.second << '\n';
    }

    return 0;
}
