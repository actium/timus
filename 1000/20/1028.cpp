#include <iostream>
#include <vector>

using point_t = std::pair<unsigned, unsigned>;

constexpr size_t R = 179;   // 179 * 179 > 32000

std::vector<point_t> p[R][R];

void solve(size_t n)
{
    unsigned s[1+R][1+R] = {};
    for (size_t i = 1; i < R; ++i) {
        for (size_t j = 1; j < R; ++j)
            s[i][j] = s[i-1][j] + s[i][j-1] - s[i-1][j-1] + p[i-1][j-1].size();
    }

    std::vector<unsigned> f(n);
    for (size_t i = 0; i < R; ++i) {
        for (size_t j = 0; j < R; ++j) {
            for (const point_t& x : p[i][j]) {
                unsigned q = s[i][j];

                for (size_t k = 0; k < i; ++k) {
                    for (const point_t& y : p[k][j])
                        q += (y.second <= x.second);
                }
                for (size_t k = 0; k < j; ++k) {
                    for (const point_t& y : p[i][k])
                        q += (y.first <= x.first);
                }
                for (const point_t& y : p[i][j]) {
                    if (y.first <= x.first && y.second <= x.second && y != x)
                        ++q;
                }

                ++f[q];
            }
        }
    }

    for (size_t i = 0; i < n; ++i)
        std::cout << f[i] << '\n';
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n;
    std::cin >> n;

    for (size_t i = 0; i < n; ++i) {
        unsigned x, y;
        std::cin >> x >> y;

        p[x/R][y/R].emplace_back(x, y);
    }

    solve(n);

    return 0;
}
