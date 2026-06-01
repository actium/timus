#include <iostream>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned a[4];
    for (size_t i = 0; i < 4; ++i)
        std::cin >> a[i];

    std::pair<unsigned, unsigned> b;
    std::cin >> b.first >> b.second;

    unsigned c;
    std::cin >> c;

    std::pair<unsigned, unsigned> x;
    std::cin >> x.first >> x.second;

    const auto next = [&](std::pair<unsigned, unsigned> q) {
        unsigned h = a[0] * q.first * q.second + a[1] * q.first + a[2] * q.second + a[3];
        if (h > b.first && h > b.second) {
            const auto d = h - b.second, k = (d + c - 1) / c;
            h -= k * c;
        }
        return std::make_pair(q.second, h);
    };

    unsigned power = 1, lambda = 1;
    for (auto slow = x, fast = next(x); fast != slow; fast = next(fast)) {
        if (power == lambda) {
            slow = fast;
            power *= 2;
            lambda = 0;
        }
        ++lambda;
    }

    auto fast = x;
    for (unsigned i = 0; i < lambda; ++i)
        fast = next(fast);

    unsigned mu = 1;
    for (auto slow = x; slow != fast; slow = next(slow)) {
        fast = next(fast);
        ++mu;
    }

    std::cout << mu << ' ' << lambda << '\n';

    return 0;
}
