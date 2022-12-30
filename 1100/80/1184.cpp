#include <iomanip>
#include <iostream>
#include <vector>

double solve(const std::vector<unsigned>& d, unsigned k)
{
    const auto check = [&](unsigned q) {
        unsigned long long c = 0;
        for (const unsigned x : d)
            c += x / q;

        return c >= k;
    };

    unsigned lb = 0, ub = 20000000;
    while (lb + 1 < ub) {
        const unsigned mid = (lb + ub) / 2;
        (check(mid) ? lb : ub) = mid;
    }

    return lb / 100.0;
}

int main()
{
    unsigned n, k;
    std::cin >> n >> k;

    std::vector<unsigned> d(n);
    for (unsigned i = 0; i < n; ++i) {
        double x;
        std::cin >> x;

        d[i] = x * 100;
    }

    std::cout << std::fixed << std::setprecision(2) << solve(d, k) << '\n';

    return 0;
}
