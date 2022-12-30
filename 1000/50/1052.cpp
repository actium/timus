#include <iostream>
#include <numeric>
#include <map>
#include <vector>

int main()
{
    size_t n;
    std::cin >> n;

    std::vector<int> xs(n), ys(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> xs[i] >> ys[i];

    const auto slope = [&](size_t i, size_t j) {
        int dx = xs[i] - xs[j], dy = ys[i] - ys[j];
        if (dx < 0) {
            dx = -dx;
            dy = -dy;
        }

        const int r = std::gcd(std::abs(dx), std::abs(dy));
        if (r != 0) {
            dx /= r;
            dy /= r;
        }

        return std::make_pair(dy, dx);
    };

    unsigned k = 0;
    {
        std::map<std::pair<int, int>, unsigned> f;
        for (size_t i = 1; i < n; ++i) {
            for (size_t j = 0; j < i; ++j)
                k = std::max(k, ++f[slope(i, j)]);

            f.clear();
        }
    }

    std::cout << k + 1 << '\n';

    return 0;
}
