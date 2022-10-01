#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    size_t n;
    std::cin >> n;

    const size_t k = n * n;

    std::vector<unsigned> h(k);
    for (size_t i = 0; i < k; ++i)
        std::cin >> h[i];

    std::sort(h.begin(), h.end(), std::greater<unsigned>());

    const auto distance = [x = n / 2](size_t r, size_t c) {
        return std::max(r, x) - std::min(r, x) + std::max(c, x) - std::min(c, x);
    };

    std::vector<std::vector<unsigned>> g(n, std::vector<unsigned>(n));
    for (size_t i = 0, d = 0; d < n; ++d) {
        for (size_t r = 0; r < n; ++r) {
            for (size_t c = 0; c < n; ++c) {
                if (distance(r, c) == d)
                    g[r][c] = h[i++];
            }
        }
    }

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j)
            std::cout << g[i][j] << ' ';

        std::cout << '\n';
    }

    return 0;
}
