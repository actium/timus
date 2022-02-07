#include <iostream>

int main()
{
    unsigned n;
    std::cin >> n;

    unsigned r = 1;
    while (n-- > 0) {
        unsigned x;
        std::cin >> x;

        r *= x % 4;
    }

    std::cout << (r % 4 == 1 ? "Stannis" : "Daenerys") << '\n';

    return 0;
}
