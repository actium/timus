#include <iostream>

using integer = unsigned long long;

integer square_root(integer n)
{
    integer x = n;
    for (integer q = 1 + x / 2; q < x; q = (x + n / x) / 2)
        x = q;

    return x;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    integer n;
    std::cin >> n;

    integer x = 1;
    for (integer i = 2; i * i * i <= n; ++i) {
        if (n % i != 0)
            continue;

        unsigned p = 0;
        while (n % i == 0) {
            n /= i;
            ++p;
        }

        for (unsigned j = 0; j < p / 2; ++j)
            x *= i * i;
    }

    const integer q = square_root(n);
    if (q * q == n)
        x *= n;

    std::cout << (x % 2 == 1 ? x : 1) << '\n';

    return 0;
}
