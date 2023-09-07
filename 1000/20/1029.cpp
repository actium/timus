#include <iostream>
#include <vector>

struct Sign {
    unsigned c = ~0u;
    size_t pi;
    size_t pj;
};

void print(const std::vector<std::vector<Sign>>& dp, size_t i, size_t j)
{
    if (i != 0)
        print(dp, dp[i][j].pi, dp[i][j].pj);

    std::cout << 1 + j << ' ';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m;
    std::cin >> n >> m;

    std::vector<std::vector<unsigned>> c(n, std::vector<unsigned>(m));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j)
            std::cin >> c[i][j];
    }

    std::vector<std::vector<Sign>> dp(n, std::vector<Sign>(m));
    for (size_t j = 0; j < m; ++j) {
        dp[0][j].c = c[0][j];
        dp[0][j].pi = 0;
        dp[0][j].pj = j;
    }

    for (size_t i = 1; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            dp[i][j].c = dp[i-1][j].c + c[i][j];
            dp[i][j].pi = i - 1;
            dp[i][j].pj = j;
        }

        for (size_t j = 1; j < m; ++j) {
            if (dp[i][j-1].c + c[i][j] < dp[i][j].c) {
                dp[i][j].c = dp[i][j-1].c + c[i][j];
                dp[i][j].pi = i;
                dp[i][j].pj = j - 1;
            }
        }
        for (size_t j = m - 1; j > 0; --j) {
            if (dp[i][j].c + c[i][j-1] < dp[i][j-1].c) {
                dp[i][j-1].c = dp[i][j].c + c[i][j-1];
                dp[i][j-1].pi = i;
                dp[i][j-1].pj = j;
            }
        }
    }

    size_t x = 0;
    for (size_t j = 1; j < m; ++j) {
        if (dp[n-1][j].c < dp[n-1][x].c)
            x = j;
    }

    print(dp, n - 1, x);

    return 0;
}
