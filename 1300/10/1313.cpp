#include <iostream>
#include <vector>

int main()
{
    size_t n;
    std::cin >> n;

    std::vector<std::vector<unsigned>> a(n, std::vector<unsigned>(n));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j)
            std::cin >> a[i][j];
    }

    for (size_t i = 0; i < 2 * n; ++i) {
        for (size_t j = 0; j <= i; ++j) {
            if (i >= j && i - j < n && j < n)
                std::cout << a[i-j][j] << ' ';
        }
    }

    return 0;
}
