#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    size_t n;
    std::cin >> n;

    std::vector<int> xs(n), ys(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> xs[i] >> ys[i];

    const auto rx = std::minmax_element(xs.begin(), xs.end());
    const auto ry = std::minmax_element(ys.begin(), ys.end());

    const int min_x = std::min(0, *rx.first), max_x = std::max(0, *rx.second);
    const int min_y = std::min(0, *ry.first), max_y = std::max(0, *ry.second);

    const size_t dx = max_x - min_x + 1, dy = max_y - min_y + 1;

    std::vector<std::vector<char>> b(dy, std::vector<char>(dx, '.'));
    for (size_t i = 0; i < dy; ++i) {
        b[i][-min_x] = '|';
    }
    for (size_t j = 0; j < dx; ++j) {
        b[-min_y][j] = '-';
    }
    b[-min_y][-min_x] = '+';

    for (size_t i = 0; i < n; ++i) {
        const size_t x = xs[i] - min_x, y = ys[i] - min_y;
        b[y][x] = '*';
    }

    for (size_t i = 0; i < dy; ++i) {
        for (size_t j = 0; j < dx; ++j)
            std::cout << b[dy - 1 - i][j];

        std::cout << '\n';
    }

    return 0;
}
