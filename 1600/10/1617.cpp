#include <iostream>

int main()
{
    unsigned n;
    std::cin >> n;

    unsigned f[101] = {};
    while (n-- > 0) {
        unsigned d;
        std::cin >> d;

        ++f[d-600];
    }

    unsigned k = 0;
    for (const unsigned x : f)
        k += x / 4;

    std::cout << k << '\n';

    return 0;
}
