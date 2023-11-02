#include <iostream>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    std::cout << '0' << '\n';
    for (unsigned i = 1; i <= n; ++i) {
        std::cout << 'X' << '\n';
        std::cout << '*' << '\n';
        std::cout << i << '\n';
        std::cout << '+' << '\n';
    }

    return 0;
}