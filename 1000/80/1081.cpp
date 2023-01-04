#include <algorithm>
#include <iostream>

int main()
{
    unsigned n, k;
    std::cin >> n >> k;

    unsigned fib[50];
    {
        unsigned a = 0, b = 1;
        for (unsigned i = 0; i < 50; ++i) {
            fib[i] = a;
            b = a + b;
            a = b - a;
        }
    }

    if (k > fib[n+2]) {
        std::cout << -1 << '\n';
    } else {
        uint64_t x = 0;
        while (k > 3) {
            const auto it = std::upper_bound(std::begin(fib), std::end(fib), k - 1) - 1;
            x |= uint64_t(1) << it - std::begin(fib) - 2;
            k -= *it;
        }
        x |= k - 1;

        for (unsigned i = n; i > 0; --i)
            std::cout << ((x & uint64_t(1) << i - 1) == 0 ? '0' : '1');
    }

    return 0;
}
