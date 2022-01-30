#include <iostream>

int main()
{
    unsigned n, k;
    std::cin >> n >> k;

    int x = k - 2;
    while (n-- > 0) {
        unsigned b, g;
        std::cin >> b >> g;

        x += b - 2 - g;
    }

    if (x < 0)
        std::cout << "Big Bang!" << '\n';
    else
        std::cout << x << '\n';

    return 0;
}
