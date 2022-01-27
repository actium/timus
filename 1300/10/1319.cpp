#include <iostream>
#include <vector>

int main()
{
    unsigned n, x = 1;
    std::cin >> n;

    std::vector<std::vector<unsigned>> t(n, std::vector<unsigned>(n));
    for (size_t i = 0; i < 2 * n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (j <= i && i - j < n)
                t[j][n-1-i+j] = x++;
        }
    }

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            std::cout << t[i][j] << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}
