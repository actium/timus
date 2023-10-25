#include <iostream>
#include <limits>

bool check(double a, unsigned n, double h)
{
    while (n > 1) {
        const double v = (a + (n - 2) * h - (n - 2) * (n - 1));
        if (v < 0)
            return false;

        h = v / --n;
    }
    return true;
}

int main()
{
    unsigned n;
    std::cin >> n;

    double a;
    std::cin >> a;

    double b = std::numeric_limits<double>::max();
    for (unsigned k = 1; (k - 1) * k <= a; ++k) {
        const double h = (a - (k - 1) * k) / k;

        const double c = (n - k - 1) * (n - k) - (n - k - 1) * h;
        if (c < 0)
            continue;

        if (c < b && check(a, n, c))
            b = c;
    }

    std::cout << std::fixed << b << '\n';

    return 0;
}
