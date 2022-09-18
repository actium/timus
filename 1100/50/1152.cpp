#include <iostream>
#include <queue>
#include <vector>

int main()
{
    constexpr unsigned oo = 1000000;

    size_t n;
    std::cin >> n;

    std::vector<unsigned> a(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> a[i];

    const auto pd = [&](unsigned m, size_t i, size_t k) {
        unsigned d = 0;
        for (size_t j = 0; j < k; ++j) {
            const size_t x = (i + j) % n;
            if (m & 1 << x)
                d += a[x];
        }
        return d;
    };

    const unsigned ub = 1 << n;

    std::vector<unsigned> dp(ub, oo);
    std::queue<unsigned> q;

    const auto enqueue = [&](unsigned x, unsigned d) {
        if (d < dp[x]) {
            dp[x] = d;
            q.push(x);
        }
    };

    for (enqueue(ub - 1, 0); !q.empty(); q.pop()) {
        const unsigned x = q.front();

        const unsigned d = pd(x, 0, n);
        for (size_t i = 0; i < n; ++i) {
            unsigned m = 0;
            for (size_t j = 0; j < 3; ++j)
                m |= 1 << (i + j) % n;

            enqueue(x & ~m, dp[x] + d - pd(x, i, 3));
        }
    }

    std::cout << dp[0] << '\n';

    return 0;
}
