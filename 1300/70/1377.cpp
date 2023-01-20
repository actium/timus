#include <iostream>
#include <vector>

int main()
{
    size_t n, m;
    std::cin >> n >> m;

    std::pair<unsigned, unsigned> p[2];
    for (auto& x : p)
        std::cin >> x.first >> x.second;

    std::vector<std::vector<int>> b(n, std::vector<int>(m));
    for (int lx = 0, x = 0, ux = m - 1, ly = 0, y = 0, uy = n - 1, dx = 1, dy = 0, t = 0; t < n * m; ++t) {
        b[y][x] = t;

        x += dx, y += dy;

        if (x < lx) {
            ++x, --y, --uy;
            dx = 0, dy = -1;
        }
        if (x > ux) {
            --x, ++y, ++ly;
            dx = 0, dy = 1;
        }
        if (y < ly) {
            ++y, ++x, ++lx;
            dx = 1, dy = 0;
        }
        if (y > uy) {
            --y, --x, --ux;
            dx = -1, dy = 0;
        }
    }

    std::cout << std::abs(b[p[0].first-1][p[0].second-1] - b[p[1].first-1][p[1].second-1]) << '\n';

    return 0;
}
