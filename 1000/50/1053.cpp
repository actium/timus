#include <iostream>
#include <numeric>

int main()
{
    size_t n;
    std::cin >> n;

    unsigned d = 0;
    for (size_t i = 0; i < n; ++i) {
        unsigned x;
        std::cin >> x;

        d = std::gcd(x, d);
    }

    std::cout << d << '\n';

    return 0;
}
