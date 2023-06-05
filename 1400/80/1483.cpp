#include <iostream>

int main()
{
    unsigned n;
    std::cin >> n;

    std::cout << n - 1 << ' ' << (n - 1) / 2 * 3 + (n % 2 == 0) << '\n';

    return 0;
}
