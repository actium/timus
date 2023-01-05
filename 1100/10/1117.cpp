#include <iostream>

unsigned count(unsigned x)
{
    const unsigned i = 32 - __builtin_clz(x);
    const unsigned d = 1 << i - 1;
    return d < x ? count(x - d) + d - 2 : d - i;
}

int main()
{
    unsigned a, b;
    std::cin >> a >> b;

    if (a > b)
        std::swap(a, b);

    std::cout << count(b) - count(a) << '\n';

    return 0;
}
