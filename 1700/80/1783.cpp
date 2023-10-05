#include <iostream>
#include <vector>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m;
    std::cin >> n >> m;

    std::vector<int> a(n + m - 1);
    for (size_t i = 0; i + 1 < n + m; ++i)
        std::cin >> a[i];

    int c = 0;
    for (size_t i = 0; i < n; ++i) {
        int x = a[i] - c;
        for (int j = 1; j < m; ++j) {
            const int d = a[i + j] - c;
            x = std::max(x, (d + (d > 0) * j) / (j + 1));
        }

        std::cout << x << ' ';

        c += x;
    }

    return 0;
}
