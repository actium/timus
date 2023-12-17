#include <iostream>
#include <vector>

#include <cmath>

struct Station {
    unsigned i;
    unsigned j;
    double r;
};

unsigned solve(const std::vector<std::vector<unsigned>>& a, const std::vector<Station>& s)
{
    const size_t n = a.size(), m = a[0].size();

    std::vector<std::vector<bool>> v(n, std::vector<bool>(m));
    for (const Station& x : s)
        v[x.i-1][x.j-1] = true;

    unsigned q = 0;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            if (v[i][j])
                continue;

            int h_min = a[i][j], h_max = 150000;
            for (const Station& x : s) {
                const int dr = i - (x.i - 1), dc = j - (x.j - 1), dp = dr * dr + dc * dc;
                if (dp > x.r * x.r) {
                    h_min = h_max;
                    break;
                }

                const int da = sqrt(x.r * x.r - dp);
                h_min = std::max<int>(h_min, a[x.i-1][x.j-1] - da);
                h_max = std::min<int>(h_max, a[x.i-1][x.j-1] + da + 1);
            }

            if (h_max > h_min)
                q += h_max - h_min;
        }
    }
    return q;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m, k;
    std::cin >> n >> m >> k;

    std::vector<std::vector<unsigned>> a(n, std::vector<unsigned>(m));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j)
            std::cin >> a[i][j];
    }

    std::vector<Station> s(k);
    for (size_t i = 0; i < k; ++i)
        std::cin >> s[i].i >> s[i].j >> s[i].r;

    std::cout << solve(a, s) << '\n';

    return 0;
}
