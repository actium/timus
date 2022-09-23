#include <array>
#include <iostream>

using integer = unsigned long long;

integer multiply(integer a, integer b, integer m)
{
    a %= m;
    b %= m;

    integer v = 0;
    for (integer y = a; b != 0; b /= 2) {
        if (b & 1)
            v = (v + y) % m;

        y = (y + y) % m;
    }
    return v;
}

std::array<integer, 4> multiply(const std::array<integer, 4>& a, const std::array<integer, 4>& b, integer m)
{
    std::array<integer, 4> c = {
        multiply(a[0], b[0], m) + multiply(a[1], b[2], m),
        multiply(a[0], b[1], m) + multiply(a[1], b[3], m),
        multiply(a[2], b[0], m) + multiply(a[3], b[2], m),
        multiply(a[2], b[1], m) + multiply(a[3], b[3], m),
    };

    for (size_t i = 0; i < 4; ++i)
        c[i] %= m;

    return c;
}

int main()
{
    integer n, k, m;
    std::cin >> n >> k >> m;

    std::array<integer, 4> v = { 1, 0, 0, 1 };
    for (std::array<integer, 4> b = { k-1, k-1, 1, 0 }; n != 0; n /= 2) {
        if (n & 1)
            v = multiply(v, b, m);

        b = multiply(b, b, m);
    }

    std::cout << v[0] << '\n';

    return 0;
}
