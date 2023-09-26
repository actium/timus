#include <iostream>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    if (n == 2) {
        std::cout << 10 << '\n';
    } else {
        for (unsigned i = 1; i < n / 2; ++i)
            std::cout << '1';

        std::cout << '0';

        for (unsigned i = 2; i < n / 2; ++i)
            std::cout << '8';

        std::cout << '9' << '0' << '\n';
    }

    return 0;
}
