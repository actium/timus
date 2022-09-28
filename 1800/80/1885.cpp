#include <iostream>

int main()
{
    double h, t, v, x;
    std::cin >> h >> t >> v >> x;

    const double t1 = (h - x * t) / (v - x), t2 = h / x;

    std::cout << std::fixed << std::max(t1, 0.0) << ' ' << std::min(t2, t) << '\n';

    return 0;
}
