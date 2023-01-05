#include <iostream>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    while (true) {
        unsigned n, p;
        std::cin >> n >> p;

        if (n == 0 && p == 0)
            break;

        unsigned long long x = 1;
        for (unsigned i = 2; i <= n; ++i) {
            x *= i;
            if (x >= p)
                x %= p;
        }
        std::cout << x << '\n';
    }

    return 0;
}
