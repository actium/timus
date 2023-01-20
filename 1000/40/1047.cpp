#include <iomanip>
#include <iostream>
#include <vector>

double solve(double a, double z, const std::vector<double>& c)
{
    const size_t n = c.size();

    double d = 0;
    for (size_t i = 0; i < n; ++i)
        d += (n - i) * 2 * c[i];

    return (z + n * a - d) / (n + 1);
}

int main()
{
    size_t n;
    std::cin >> n;

    double a, z;
    std::cin >> a >> z;

    std::vector<double> c(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> c[i];

    std::cout << std::fixed << std::setprecision(2) << solve(a, z, c) << '\n';

    return 0;
}
