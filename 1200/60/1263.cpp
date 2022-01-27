#include <iostream>
#include <iomanip>
#include <vector>

int main()
{
    size_t n, m;
    std::cin >> n >> m;

    std::vector<unsigned> f(n);
    for (size_t i = 0; i < m; ++i) {
        unsigned x;
        std::cin >> x;

        ++f[x-1];
    }

    for (size_t i = 0; i < n; ++i)
        std::cout << std::fixed << std::setprecision(2) << f[i] * 100.0 / m << '%' << '\n';

    return 0;
}
