#include <iostream>

int main()
{
    constexpr size_t t[8] = { 7, 6, 5, 0, 4, 1, 2, 3 };

    unsigned a[8];

    for (size_t i = 0; i < 7; ++i)
        std::cin >> a[i];

    const unsigned r1 = a[1] ^ a[2] ^ a[3];
    const unsigned r2 = a[0] ^ a[2] ^ a[3];
    const unsigned r3 = a[0] ^ a[1] ^ a[3];

    a[t[4 * (r1 != a[4]) + 2 * (r2 != a[5]) + 1 * (r3 != a[6])]] ^= 1;

    for (size_t i = 0; i < 7; ++i)
        std::cout << a[i] << ' ';

    return 0;
}
