#include <algorithm>
#include <iostream>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int min_x = 1e9, max_x = -1e9, min_y = 1e9, max_y = -1e9;
    for (int x1, y1, x2, y2; std::cin >> x1 >> y1 >> x2 >> y2; ) {
        const int x = x1 + x2 + y1 - y2, y = y1 + y2 + x2 - x1;
        min_x = std::min({ min_x, 2 * x1, 2 * x2, x });
        max_x = std::max({ max_x, 2 * x1, 2 * x2, x });
        min_y = std::min({ min_y, 2 * y1, 2 * y2, y });
        max_y = std::max({ max_y, 2 * y1, 2 * y2, y });
    }

    std::cout << std::fixed << std::max((max_x - min_x) / 2.0, 0.0) << ' ' << std::max((max_y - min_y) / 2.0, 0.0) << '\n';

    return 0;
}
