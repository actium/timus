#include <iostream>

int main()
{
    unsigned n, k;
    std::cin >> n >> k;

    unsigned a = 1;
    for (unsigned b = k - 1; n != 0; --n) {
        const unsigned c = (k - 1) * (a + b);
        a = b;
        b = c;
    }

    std::cout << a << '\n';

    return 0;
}
