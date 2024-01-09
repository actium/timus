#include <iomanip>
#include <iostream>

#include <cmath>

const double pi = acos(-1);

int main()
{
    double a1, b1, a2, b2;
    std::cin >> a1 >> b1 >> a2 >> b2;

    const auto f = [=](double x) {
        const auto sx = sin(x), cx = cos(x);
        return hypot(sx * a1 + cx * b1, sx * a2 + cx * b2);
    };

    double lb = 0, ub = 2 * pi;
    for (unsigned i = 0; i < 100; ++i) {
        const double d = (ub - lb) / 3;
        f(lb + d) > f(ub - d) ? ub -= d : lb += d;
    }

    std::cout << std::fixed << std::setprecision(9) << f(lb) << '\n';

    return 0;
}
