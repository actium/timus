#include <iostream>

int main()
{
    using integer = long long;

    unsigned s;
    std::cin >> s;

    for (integer n = 45000; n > 0; --n) {
        const integer q = 2 * s - n * (n + 1);
        if (q % (2 * n) != 0)
            continue;

        const integer a = q / (2 * n) + 1;
        if (a > 0) {
            std::cout << a << ' ' << n << '\n';
            break;
        }
    }

    return 0;
}
