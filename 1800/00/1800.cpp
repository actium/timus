#include <iostream>

#include <cmath>

const char* solve(unsigned l, unsigned h, unsigned w)
{
    if (l < 2 * h) {
#if false   // failed test cases: (701, 903, 212) and (1000, 1000, 1000)
        const auto x = (2 * h - l) * w * w % 3531600;
        if (x > 220725 && x < 1986525)
#else
        const double t = sqrt((2 * h - l) / 981.0), a = t * w / 60 - int(t * w / 60);
        if (a > 0.25 && a < 0.75)
#endif
            return "bread";
    }
    return "butter";
}

int main()
{
    unsigned l, h, w;
    std::cin >> l >> h >> w;

    std::cout << solve(l, h, w) << '\n';

    return 0;
}
