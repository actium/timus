#include <iostream>
#include <vector>

#include <cmath>

const double dd = sqrt(100 * 100 + 100 * 100);

int main()
{
    unsigned n, m;
    std::cin >> n >> m;

    unsigned k;
    std::cin >> k;

    std::vector<std::vector<bool>> b(1+n, std::vector<bool>(1+m));
    while (k-- > 0) {
        unsigned r, c;
        std::cin >> r >> c;

        b[r][c] = true;
    }

    std::vector<std::vector<double>> d(1+n, std::vector<double>(1+m));
    for (size_t i = 1; i <= n; ++i) {
        d[i][0] = d[i-1][0] + 100;
    }
    for (size_t j = 1; j <= m; ++j) {
        d[0][j] = d[0][j-1] + 100;
    }
    for (size_t i = 1; i <= n; ++i) {
        for (size_t j = 1; j <= m; ++j) {
            d[i][j] = std::min(d[i-1][j], d[i][j-1]) + 100;

            if (b[i][j])
                d[i][j] = std::min(d[i][j], d[i-1][j-1] + dd);
        }
    }

    std::cout << int(d[n][m] + 0.5) << '\n';

    return 0;
}
