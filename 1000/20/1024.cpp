#include <iostream>
#include <numeric>
#include <vector>

unsigned period(const std::vector<unsigned>& p, size_t x)
{
    unsigned k = 1;
    for (size_t i = x; p[i] != x + 1; i = p[i] - 1)
        ++k;

    return k;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<unsigned> p(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> p[i];

    unsigned k = 1;
    for (size_t i = 0; i < n; ++i)
        k = std::lcm(k, period(p, i));

    std::cout << k << '\n';

    return 0;
}
