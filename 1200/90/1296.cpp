#include <iostream>

int main()
{
    unsigned n;
    std::cin >> n;

    int x = 0, y = 0;
    while (n-- > 0) {
        int p;
        std::cin >> p;

        x = std::max(p, x + p);
        y = std::max(y, x);
    }

    std::cout << y << '\n';

    return 0;
}
