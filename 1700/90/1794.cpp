#include <iostream>
#include <vector>

int main()
{
    size_t n;
    std::cin >> n;

    std::vector<unsigned> f(n);
    for (unsigned i = 1; i <= n; ++i) {
        unsigned x;
        std::cin >> x;

        ++f[(n+i-x)%n];
    }

    size_t x = 0;
    for (size_t i = 1; i < n; ++i) {
        if (f[i] > f[x])
            x = i;
    }

    std::cout << 1 + x << '\n';

    return 0;
}
