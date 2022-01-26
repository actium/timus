#include <iostream>
#include <vector>

int main()
{
    size_t n;
    std::cin >> n;

    std::vector<unsigned> a(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> a[i];

    size_t x = 2;
    for (size_t i = 3; i < n; ++i) {
        if (a[i-2] + a[i-1] + a[i] > a[x-2] + a[x-1] + a[x])
            x = i;
    }

    std::cout << a[x-2] + a[x-1] + a[x] << ' ' << x << '\n';

    return 0;
}
