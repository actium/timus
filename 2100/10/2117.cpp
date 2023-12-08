#include <iostream>

#include <cmath>

using integer = unsigned long long;

integer square_root(integer n)
{
    const integer x = sqrt(n);
    return x + (x * x < n);
}

integer solve(integer n)
{
    if (n == 0)
        return 1;

    integer k = 1;
    for (integer i = 2; i * i * i <= n; ++i) {
        while (n % (i * i) == 0) {
            k *= i;
            n /= i * i;
        }

        while (n % i == 0)
            n /= i;
    }
    for (integer x = square_root(n); x != 1 && x * x == n; x = square_root(n)) {
        k *= x;
        n /= x * x;
    }

    return 1 + k / 2;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    integer n;
    std::cin >> n;

    std::cout << solve(n) << '\n';

    return 0;
}
