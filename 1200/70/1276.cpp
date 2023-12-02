#include <array>
#include <iostream>
#include <vector>

using integer = unsigned long long;

integer solve(const std::array<unsigned, 4>& f, const std::string& c, size_t k)
{
    const auto index = [&](size_t c, size_t q1, size_t q2, size_t q3, size_t q4) {
        return (((c * (f[0] + 1) + q1) * (f[1] + 1) + q2) * (f[2] + 1) + q3) * (f[3] + 1) + q4;
    };

    const size_t m = index(2, 0, 0, 0, 0);

    std::vector<integer> dp(m);
    dp[index(c[1] - 'A', 0, 0, 0, 0)] = 1;
    for (size_t l = 0; l < k; ++l) {
        std::vector<integer> ndp(m);
        for (unsigned i1 = 0; i1 <= f[0]; ++i1) {
            for (unsigned i2 = 0; i2 <= f[1]; ++i2) {
                for (unsigned i3 = 0; i3 <= f[2]; ++i3) {
                    for (unsigned i4 = 0; i4 <= f[3]; ++i4) {
                        if (i1 < f[0])
                            ndp[index(0, i1+1, i2, i3, i4)] += dp[index(0, i1, i2, i3, i4)];

                        if (i2 < f[1])
                            ndp[index(1, i1, i2+1, i3, i4)] += dp[index(0, i1, i2, i3, i4)];

                        if (i3 < f[2])
                            ndp[index(0, i1, i2, i3+1, i4)] += dp[index(1, i1, i2, i3, i4)];

                        if (i4 < f[3])
                            ndp[index(1, i1, i2, i3, i4+1)] += dp[index(1, i1, i2, i3, i4)];
                    }
                }
            }
        }
        dp.swap(ndp);
    }

    integer q = 0;
    for (unsigned i1 = 0; i1 <= f[0]; ++i1) {
        for (unsigned i2 = 0; i2 <= f[1]; ++i2) {
            for (unsigned i3 = 0; i3 <= f[2]; ++i3) {
                for (unsigned i4 = 0; i4 <= f[3]; ++i4)
                    q += dp[index(c[0] - 'A', i1, i2, i3, i4)];
            }
        }
    }
    return q;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, k;
    std::cin >> n >> k;

    std::string c;
    std::cin >> c;

    std::array<unsigned, 4> f = {};
    for (size_t i = 0; i < n; ++i) {
        std::string x;
        std::cin >> x;

        ++f[(x[0] - 'A') * 2 + (x[1] - 'A')];
    }

    const integer q = solve(f, c, k);
    if (q == 0) {
        std::cout << "NO" << '\n';
    } else {
        std::cout << "YES" << '\n';
        std::cout << q << '\n';
    }

    return 0;
}
