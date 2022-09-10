#include <iomanip>
#include <iostream>

#include <cmath>

int main()
{
    unsigned v, a;
    std::cin >> v >> a;

    double k;
    std::cin >> k;

    const double r = 3.1415926535 * a / 180;
    const double d = k * std::sin(2 * r) * v * v * 0.1 / (k - 1);

    std::cout << std::fixed << std::setprecision(2) << d << '\n';

    return 0;
}
