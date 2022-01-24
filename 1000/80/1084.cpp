#include <iomanip>
#include <iostream>

#define _USE_MATH_DEFINES
#include <cmath>

void solve(unsigned s, unsigned r)
{
    std::cout << std::fixed << std::setprecision(3);

    if (s * s <= 2 * r * r) {
        std::cout << s * s << '\n';
        return;
    }

    if (2 * r <= s) {
        std::cout << M_PI * r * r << '\n';
        return;
    }

    const double h = sqrt(r * r - s * s / 4.0);
    const double a = atan2(h, s / 2.0);
    const double d = r * r * a - s * h / 2;

    std::cout << M_PI * r * r - 4 * d << '\n';
}

int main()
{
    unsigned s, r;
    std::cin >> s >> r;

    solve(s, r);

    return 0;
}
