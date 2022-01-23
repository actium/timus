#include <iostream>

int main()
{
    unsigned a[100000] = { 0, 1 };
    for (size_t i = 1; i < 50000; ++i) {
        a[2 * i] = a[i];
        a[2 * i + 1] = a[i] + a[i + 1];
    }

    for (unsigned i = 2; i < 100000; ++i)
        a[i] = std::max(a[i], a[i-1]);

    for (unsigned n; std::cin >> n && n != 0; std::cout << a[n] << '\n');

    return 0;
}
