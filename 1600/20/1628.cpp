#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned m, n, k;
    std::cin >> m >> n >> k;

    std::vector<std::vector<unsigned>> r(m, {0, n + 1}), c(n, {0, m + 1});
    for (unsigned i = 0; i < k; ++i) {
        unsigned x, y;
        std::cin >> x >> y;

        r[x-1].push_back(y);
        c[y-1].push_back(x);
    }

    unsigned q = 0;
    {
        std::vector<std::pair<unsigned, unsigned>> e;

        for (unsigned i = 0; i < m; ++i) {
            std::sort(r[i].begin(), r[i].end());

            for (size_t j = 1; j < r[i].size(); ++j) {
                const unsigned d = r[i][j] - r[i][j-1];
                if (d == 2)
                    e.emplace_back(i + 1, r[i][j] - 1);

                q += (d > 2);
            }
        }

        for (unsigned i = 0; i < n; ++i) {
            std::sort(c[i].begin(), c[i].end());

            for (size_t j = 1; j < c[i].size(); ++j) {
                const unsigned d = c[i][j] - c[i][j-1];
                if (d == 2)
                    e.emplace_back(c[i][j] - 1, i + 1);

                q += (d > 2);
            }
        }

        std::sort(e.begin(), e.end());
        for (size_t i = 1; i < e.size(); ++i)
            q += (e[i] == e[i-1]);
    }

    std::cout << q << '\n';

    return 0;
}
