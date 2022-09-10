#include <iostream>

int main()
{
    double k1, k2, k3;
    std::cin >> k1 >> k2 >> k3;

    const double f = 1.0 + k1 / k2 + k1 / k3;
    std::cout << int(1000.0 / f * k1 + 0.5) << '\n';

    return 0;
}
