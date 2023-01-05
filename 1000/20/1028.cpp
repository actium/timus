#include <iostream>
#include <vector>

constexpr size_t N = 1 + 32000;

inline size_t lsb(size_t x)
{
    return x & -x;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<unsigned> q(1 + N);

    const auto update = [&q](size_t index) {
        for (size_t i = 1 + index; i <= N; i += lsb(i))
            ++q[i];
    };

    const auto count = [&q](size_t index) {
        unsigned k = 0;
        for (size_t i = 1 + index; i > 0; i &= ~lsb(i))
            k += q[i];

        return k;
    };

    size_t n;
    std::cin >> n;

    std::vector<unsigned> f(n);
    for (size_t i = 0; i < n; ++i) {
        unsigned x, y;
        std::cin >> x >> y;

        ++f[count(x)];
        update(x);
    }

    for (const unsigned x : f)
        std::cout << x << '\n';

    return 0;
}
