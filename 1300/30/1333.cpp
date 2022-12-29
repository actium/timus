#include <iostream>

int main()
{
    constexpr unsigned X = 200;

    size_t n;
    std::cin >> n;

    unsigned g[1+X][1+X] = {};
    for (size_t i = 0; i < n; ++i) {
        double x, y, r;
        std::cin >> x >> y >> r;

        x *= X, y *= X, r *= X;
        for (size_t i = 0; i <= X; ++i) {
            for (size_t j = 0; j <= X; ++j) {
                const auto dx = j - x, dy = i - y;
                if (dx * dx + dy * dy <= r * r)
                    g[i][j] = 1;
            }
        }
    }

    unsigned k = 0;
    for (size_t i = 0; i <= X; ++i) {
        for (size_t j = 0; j <= X; ++j)
            k += g[i][j];
    }

    std::cout << std::fixed << 100.0 * k / (X * X) << '\n';

    return 0;
}
