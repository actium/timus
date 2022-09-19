#include <iostream>

int main()
{
    unsigned m, d1, d2;
    std::cin >> m >> d1 >> d2;

    unsigned t = m * d1;
    for (unsigned i = 0; i < d2; ++i) {
        const unsigned k = t / (d2 - i);
        std::cout << k << ' ';
        t -= k;
    }

    return 0;
}
