#include <iostream>

unsigned raise(unsigned long long b, unsigned p, unsigned m)
{
    unsigned long long v = 1;
    while (p != 0) {
        if (p & 1)
            v = v * b % m;

        b = b * b % m;
        p /= 2;
    }
    return v;
}

int main()
{
    unsigned n, m, y;
    std::cin >> n >> m >> y;

    const char* s = "-1";
    for (unsigned x = 0; x < m; ++x) {
        if (raise(x, n, m) == y) {
            std::cout << x << ' ';
            s = "";
        }
    }
    std::cout << s << '\n';

    return 0;
}
