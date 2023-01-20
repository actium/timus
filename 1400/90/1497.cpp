#include <iostream>
#include <string>
#include <vector>

const char* solve(const std::vector<std::string>& g)
{
    const size_t n = g.size();

    bool p[4] = { true, true, true, true };
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (g[i][j] == '1')
                continue;

            p[0] = p[0] && (i == 0 || g[i - 1][j] == '0');
            p[1] = p[1] && (j + 1 == n || g[i][j + 1] == '0');
            p[2] = p[2] && (i + 1 == n || g[i + 1][j] == '0');
            p[3] = p[3] && (j == 0 || g[i][j - 1] == '0');
        }
    }

    return p[0] || p[1] || p[2] || p[3] ? "Yes" : "No";
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n;
    std::cin >> n;

    std::vector<std::string> g(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> g[i];

    std::cout << solve(g) << '\n';

    return 0;
}
