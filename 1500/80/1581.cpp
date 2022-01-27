#include <iostream>

int main()
{
    unsigned n;
    std::cin >> n;

    unsigned p = 0, q = 0;
    while (n-- != 0) {
        unsigned x;
        std::cin >> x;

        if (x != p && q != 0) {
            std::cout << q << ' ' << p << ' ';
            p = x, q = 0;
        }

        p = x, ++q;
    }
    std::cout << q << ' ' << p << '\n';

    return 0;
}
