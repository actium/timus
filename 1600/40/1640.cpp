#include <iomanip>
#include <iostream>

#include <cmath>

int main()
{
    size_t n;
    std::cin >> n;

    double r = 0;
    for (size_t i = 0; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;

        r = std::max(r, std::hypot(x, y));
    }

    std::cout << 0 << ' ' << 0 << ' ' << std::fixed << std::setprecision(10) << r << '\n';

    return 0;
}
