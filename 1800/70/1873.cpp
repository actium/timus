#include <iostream>

int main()
{
    unsigned n;
    std::cin >> n;

    constexpr unsigned k[] = { 5, 21, 12, 2, 1, 4, 6, 1, 4, 4, 1, 0, 1, 1 };
    std::cout << k[n] << '\n';

    return 0;
}
