#include <iostream>

int main()
{
    constexpr unsigned f[2][3] = {
        { 16, 8, 4 }, { 16, 4, 3 },
    };

    unsigned wt, ws;
    std::cin >> wt >> ws;

    const unsigned b = ws * ws * f[0][wt-1];

    size_t n;
    std::cin >> n;

    unsigned k = 0;
    for (size_t i = 0; i < n; ++i) {
        unsigned t, s;
        std::cin >> t >> s;

        if (s * s * f[1][t-1] <= b)
            ++k;
    }

    std::cout << k << '\n';

    return 0;
}
