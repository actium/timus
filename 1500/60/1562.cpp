#include <iostream>

constexpr double pi = 3.14159265358979323846;

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    double a, b;
    std::cin >> a >> b;

    unsigned n;
    std::cin >> n;

    const double p = a * a / 4, q = 3 * b * b / 4, r = b / 2, d = b / n;

    const auto f = [=](double x) {
        return pi * p * x * (1 - x * x / q);
    };

    double u = f(-r);
    for (unsigned i = 1; i <= n; ++i) {
        const double v = f(i * d - r);
        std::cout << std::fixed << v - u << '\n';
        u = v;
    }

    return 0;
}
