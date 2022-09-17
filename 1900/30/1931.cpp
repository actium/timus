#include <iostream>
#include <vector>

int main()
{
    size_t n;
    std::cin >> n;

    std::vector<unsigned> a(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> a[i];

    std::vector<unsigned> f(n);
    for (size_t x = 0, i = 1; i < n; ++i) {
        ++f[x];
        ++f[i];

        if (a[i] < a[x])
            x = i;
    }

    size_t x = 0;
    for (size_t i = 1; i < n; ++i) {
        if (f[i] > f[x])
            x = i;
    }

    std::cout << 1+x << '\n';

    return 0;
}
