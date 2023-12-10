#include <iostream>

#include <cmath>

const double pi = acos(-1);

int main()
{
    double h, w;
    std::cin >> h >> w;

    double x, y;
    std::cin >> x >> y;

    double r;
    std::cin >> r;

    const double vp = w * w * h / 3;
    const double hc = h * (w / 2 - std::max(std::abs(x), std::abs(y))) * 2 / w;
    const double vc = pi * r * r * hc;

    std::cout << std::fixed << vp - vc << '\n';;

    return 0;
}
