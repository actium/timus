#include <limits>
#include <vector>

#include <cstdio>

const double oo = std::numeric_limits<double>::max();

void solve(unsigned m, const std::vector<int>& k, const std::vector<int>& p, const std::vector<int>& q)
{
    const size_t n = k.size();

    std::vector<double> dp(1 + m, oo);
    dp[0] = 0;
    for (size_t i = 0; i < n; ++i) {
        const double d = (k[i] > 1 ? (q[i] - p[i]) / (k[i] - 1.0) : 0);

        std::vector<double> t = dp;
        for (int j = 1; j <= k[i]; ++j) {
            for (unsigned c = m; c >= j; --c) {
                if (dp[c-j] != oo) {
                    const double v = j * (2 * p[i] + d * (j - 1)) / 2;
                    t[c] = std::min(t[c], dp[c-j] + v);
                }
            }
        }
        dp = std::move(t);
    }

    unsigned x = m;
    while (x > 0 && dp[x] == oo)
        --x;

    if (x < m)
        printf("Maximum possible amount: %d\n", x);

    printf("Minimum possible cost: %.02f\n", dp[x]);
}

int main()
{
    unsigned n, m;
    scanf("%u %u", &n, &m);

    std::vector<int> k(n), p(n), q(n);
    for (size_t i = 0; i < n; ++i)
        scanf("%d %d %d", &k[i], &p[i], &q[i]);

    solve(m, k, p, q);

    return 0;
}
