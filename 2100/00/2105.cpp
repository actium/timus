#include <iostream>

int main()
{
    unsigned d, t, v[2];
    std::cin >> d >> t >> v[0] >> v[1];

    size_t n;
    std::cin >> n;

    unsigned r[2] = {};
    for (size_t i = 0; i < n; ++i) {
        unsigned x, t, d;
        std::cin >> x >> t >> d;

        r[x-1] += d;
    }

    std::cout << ((t - r[0]) * v[0] + (t - r[1]) * v[1]) / d << '\n';

    return 0;
}
