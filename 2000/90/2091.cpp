#include <iostream>
#include <vector>

int main()
{
    size_t n, m;
    std::cin >> n >> m;

    std::vector<std::vector<unsigned>> a(n, std::vector<unsigned>(m));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j)
            std::cin >> a[i][j];
    }

    const auto f = [&](size_t i, size_t j) {
        unsigned s[4] = {};
        for (size_t k = 0; k < n; ++k) {
            s[0] += (a[k][j] == 1 && a[k][i] == 1);
            s[1] += (a[k][j] == 1 && a[k][i] == 0);
            s[2] += (a[k][j] == 0 && a[k][i] == 1);
            s[3] += (a[k][j] == 0 && a[k][i] == 0);
        }
        return std::max(std::max(s[0], s[1]), std::max(s[2], s[3]));
    };

    std::pair<size_t, size_t> x = { 0, 1 };
    for (size_t i = 2; i < m; ++i) {
        for (size_t j = 0; j < i; ++j) {
            if (f(i, j) < f(x.first, x.second))
                x = std::make_pair(i, j);
        }
    }

    std::cout << f(x.first, x.second) << '\n';
    std::cout << 1 + x.first << ' ' << 1 + x.second << '\n';

    return 0;
}
