#include <iostream>
#include <vector>

unsigned long long round(double x)
{
    const auto epsilon = 1e-8;
    return x + epsilon;
}

unsigned solve(const std::vector<double>& c, unsigned k)
{
    const size_t n = c.size();

    unsigned m = 1;
    while (k-- != 0)
        m *= 10;

    const auto check = [&](unsigned x) {
        for (size_t i = 0; i < n; ++i) {
            const auto r = round(c[i] * m) * x % m;
            if (2 * r > x && x <= 2 * (m - r))
                return false;
        }
        return true;
    };

    unsigned x = 1;
    while (!check(x))
        ++x;

    return x;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned k;
    std::cin >> k;

    size_t n;
    std::cin >> n;

    std::vector<double> c(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> c[i];

    std::cout << solve(c, k) << '\n';

    return 0;
}
