#include <iostream>

#include <cmath>

double P[201];

double C(unsigned n, unsigned k)
{
    return P[n] - P[k] - P[n-k];
}

double t[201][21];

double solve(unsigned n, unsigned k)
{
    if (k == 0)
        return n;

    if (2 * k >= n)
        return 0;

    n -= k;

    if (t[n][k] == 0) {
        for (unsigned d = 1; d <= n; ++d) {
            double v = 0;
            for (unsigned q = 0; q <= std::min(k, d); ++q) {
                if (d - q <= n - k) {
                    const auto p = std::exp(C(k, q) + C(n - k, d - q) - C(n, d));
                    v += solve(n - d, k - q) * p;
                }
            }

            t[n][k] = std::max(t[n][k], v);
        }
    }
    return t[n][k];
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    for (unsigned i = 1; i <= 200; ++i)
        P[i] = P[i-1] + std::log(i);

    unsigned n, k;
    std::cin >> n >> k;

    std::cout << std::fixed << solve(n, k) << '\n';

    return 0;
}
