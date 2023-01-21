#include <iostream>

constexpr unsigned N = 1000;

unsigned dp[1+N][1+N];

void initialize()
{
    unsigned h[1+N][1+N] = {};
    for (unsigned i = 1, j = 1; i <= N; ++j) {
        h[i][j] = h[i][j-1] + h[i-1][j-1] + 1;

        if (h[i][j] >= N) {
            h[i][j] = N;
            ++i, j = 0;
        }
    }

    for (unsigned i = 1; i <= N; ++i) {
        for (unsigned j = 1, k = 0; h[i][j-1] != N; ++j) {
            while (k < h[i][j])
                dp[i][++k] = j;
        }
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    initialize();

    unsigned e, f;
    for (std::cin >> e >> f; e != 0 || f != 0; std::cin >> e >> f)
        std::cout << dp[e][f] << '\n';

    return 0;
}
