#include <iostream>

using integer = unsigned long long;

int main()
{
    unsigned a, b, n;
    std::cin >> a >> b >> n;

    integer k = 0;
    for (unsigned x = 0, d; x < n; x += d) {
        d = std::min(a, n - x);

        const integer p = std::min<integer>(d, b - x % b), r = d - p, q = r / b;
        k += b * q * b * (q - 1) / 2 + p * (r - b * q) + b * q * (p + r - b * q);
    }

    std::cout << k << '\n';

    return 0;
}
