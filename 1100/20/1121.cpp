#include <iostream>
#include <vector>

int search(const std::vector<std::vector<unsigned>>& a, int i, int j)
{
    const size_t h = a.size(), w = a[0].size();

    if (a[i][j] != 0)
        return -1;

    unsigned v[6] = {};
    for (int di = -5; di <= +5; ++di) {
        const int r = i + di;
        if (r < 0 || r >= h)
            continue;

        for (int dj = -5; dj <= +5; ++dj) {
            const int c = j + dj;
            if (c < 0 || c >= w)
                continue;

            const int d = std::abs(di) + std::abs(dj);
            if (d < 6)
                v[d] |= a[r][c];
        }
    }

    for (size_t i = 0; i < 6; ++i) {
        if (v[i] != 0)
            return v[i];
    }
    return 0;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t h, w;
    std::cin >> h >> w;

    std::vector<std::vector<unsigned>> a(h, std::vector<unsigned>(w));
    for (size_t i = 0; i < h; ++i) {
        for (size_t j = 0; j < w; ++j)
            std::cin >> a[i][j];
    }

    for (size_t i = 0; i < h; ++i) {
        for (size_t j = 0; j < w; ++j)
            std::cout << search(a, i, j) << ' ';

        std::cout << '\n';
    }

    return 0;
}
