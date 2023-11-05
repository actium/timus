#include <iostream>

int main()
{
    unsigned n;
    std::cin >> n;

    if (n % 2 == 0 || n % 3 == 0) {
        std::cout << "No" << '\n';
    } else {
        std::cout << "Yes" << '\n';
        for (unsigned i = 0; i < n; ++i) {
            std::cout << 1 + i * 2 % n << ' ';
        }
    }

    return 0;
}
