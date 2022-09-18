#include <iostream>
#include <vector>

int main()
{
    size_t n;
    std::cin >> n;

    std::vector<unsigned> a(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> a[i];

    unsigned s = 0;
    for (size_t i = 0; i < n; ++i)
        s += a[i];

    std::vector<unsigned> v(n);
    for (size_t i = 0; i < n; ++i) {
        if (a[i] * (n + 1) > s)
            v[i] = a[i] * (n + 1) - s;
    }

    unsigned t = 0;
    for (size_t i = 0; i < n; ++i)
        t += v[i];

    for (size_t i = 0; i < n; ++i)
        std::cout << 100 * v[i] / t << ' ';

    return 0;
}
