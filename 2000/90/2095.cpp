#include <iostream>

unsigned count(unsigned b)
{
    for (unsigned k = 2; b >= k; ++k)
        b -= b / k;

    return b;
}

int main()
{
    unsigned l, r;
    std::cin >> l >> r;

    std::cout << count(r) - count(l-1) << '\n';

    return 0;
}
