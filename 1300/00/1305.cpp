#include <iostream>

constexpr unsigned oo = ~0u;

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    unsigned b[] = { oo, oo, oo, oo, 0, 0, 0, 0  };
    for (size_t i = 0; i < n; ++i) {
        unsigned x, y;
        std::cin >> x >> y;

        const unsigned p = x + y, q = 1000 - x + y;
        b[0] = std::min(b[0], x);
        b[1] = std::min(b[1], y);
        b[2] = std::min(b[2], p);
        b[3] = std::min(b[3], q);
        b[4] = std::max(b[4], x);
        b[5] = std::max(b[5], y);
        b[6] = std::max(b[6], p);
        b[7] = std::max(b[7], q);
    }

    const std::pair<unsigned, unsigned> p[8] = {
        std::make_pair(b[2] - b[1], b[1]),
        std::make_pair(b[1] + (1000 - b[3]), b[1]),
        std::make_pair(b[4], b[4] - (1000 - b[3])),
        std::make_pair(b[4], b[6] - b[4]),
        std::make_pair(b[6] - b[5], b[5]),
        std::make_pair(b[5] + (1000 - b[7]), b[5]),
        std::make_pair(b[0], b[0] - (1000 - b[7])),
        std::make_pair(b[0], b[2] - b[0]),
    };

    std::cout << p[0].first << ' ' << p[0].second << '\n';
    for (size_t i = 1; i < 8; ++i) {
        if (p[i] != p[i-1] && p[i] != p[0])
            std::cout << p[i].first << ' ' << p[i].second << '\n';
    }

    return 0;
}
