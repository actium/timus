#include <iostream>
#include <numeric>

int main()
{
    unsigned n, m;
    std::cin >> n >> m;
    --n, --m;

    std::cout << n + m - std::gcd(n, m) << '\n';

    return 0;
}
