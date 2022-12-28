#include <iostream>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n, m;
    std::cin >> n >> m;

    unsigned r[2][3072];
    for (size_t j = 0; j < m; ++j)
        std::cin >> r[0][j];

    const char* v = "Yes";
    for (size_t i = 1; i < n; ++i) {
        for (size_t j = 0; j < m; ++j)
            std::cin >> r[i % 2][j];

        for (size_t j = 1; j < m; ++j) {
            if (r[0][j-1] + r[0][j] + r[1][j-1] + r[1][j] == 3)
                v = "No";
        }
    }

    std::cout << v << '\n';

    return 0;
}
