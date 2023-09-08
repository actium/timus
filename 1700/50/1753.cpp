#include <iostream>

#include <cmath>

constexpr double PI = 3.1415926535897932384626433832795;

int main()
{
    unsigned h, b, l;
    std::cin >> h >> b >> l;

    const auto check = [=](double x) {
        const double s = sin(x), ss = s * s;
        return h / ss - s * b / 2 >= 0;
    };

    double lb = 0, ub = PI / 2;
    for (unsigned i = 0; i < 100; ++i) {
        const double mid = (lb + ub) / 2;

        (check(mid) ? lb : ub) = mid;
    }

    std::cout << std::fixed << b * cos(lb) / 2 - h / tan(lb) << '\n';

    return 0;
}
